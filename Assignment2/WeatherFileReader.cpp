// WeatherFileReader.cpp
//
// Implementation of weather file loading and parsing functions.
// Reads configured CSV files, detects columns, parses values, and stores records in the weather model.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial WeatherFileReader implementation.
// 02 01/03/2026 Heng Kiao Woon - Refined parsing support and delimiter handling.
// 03 03/04/2026 Heng Kiao Woon - Updated file header.
//---------------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Includes
#include "WeatherFileReader.h"
#include "Utility.h"

#include <fstream>
#include <iostream>

//----------------------------------------------------------------------------
// Detect delimiter (tab preferred if present, else comma).
static char DetectDelimiterCharacter(const std::string& headerLine)
{
    for (size_t characterIndex = 0;
            characterIndex < headerLine.length();
            ++characterIndex)
    {
        if (headerLine[characterIndex] == '\t')
        {
            return '\t';
        }
    }

    return ',';
}

//----------------------------------------------------------------------------
// Extracts a field by column index from a delimited line.
static std::string ExtractFieldByColumnIndex(const std::string& dataLine,
        int targetColumnIndex,
        char delimiterCharacter)
{
    int currentColumnIndex = 0;
    size_t startPosition = 0;

    while (startPosition <= dataLine.length())
    {
        size_t delimiterPosition = dataLine.find(delimiterCharacter, startPosition);
        std::string currentCellValue;

        if (delimiterPosition == std::string::npos)
        {
            currentCellValue = dataLine.substr(startPosition);
            startPosition = dataLine.length() + 1;
        }
        else
        {
            currentCellValue = dataLine.substr(startPosition, delimiterPosition - startPosition);
            startPosition = delimiterPosition + 1;
        }

        if (currentColumnIndex == targetColumnIndex)
        {
            currentCellValue = Trim(currentCellValue);

            if (!currentCellValue.empty() && currentCellValue.back() == '\r')
            {
                currentCellValue.pop_back();
            }

            return currentCellValue;
        }

        ++currentColumnIndex;
    }

    return "";
}

//----------------------------------------------------------------------------
// Parses an integer from a string (manual parse, no sstream).
static bool ParseIntegerValue(const std::string& inputText,
                              size_t& currentPosition,
                              int& outputValue)
{
    while (currentPosition < inputText.length() &&
            IsWhitespaceCharacter(inputText[currentPosition]))
    {
        ++currentPosition;
    }

    bool isNegativeNumber = false;

    if (currentPosition < inputText.length() &&
            (inputText[currentPosition] == '-' || inputText[currentPosition] == '+'))
    {
        isNegativeNumber = (inputText[currentPosition] == '-');
        ++currentPosition;
    }

    bool containsDigit = false;
    int numericValue = 0;

    while (currentPosition < inputText.length() &&
            inputText[currentPosition] >= '0' &&
            inputText[currentPosition] <= '9')
    {
        containsDigit = true;
        numericValue = numericValue * 10 + (inputText[currentPosition] - '0');
        ++currentPosition;
    }

    if (!containsDigit)
    {
        return false;
    }

    outputValue = isNegativeNumber ? -numericValue : numericValue;
    return true;
}

//----------------------------------------------------------------------------
// Parses a simple float value (manual parse). Returns false for NA/blank values.
static bool ParseFloatingPointValue(const std::string& rawText, float& outputValue)
{
    std::string trimmedText = Trim(rawText);

    if (trimmedText.empty())
    {
        return false;
    }

    if (EqualsIgnoreCase(trimmedText, "NA") ||
            EqualsIgnoreCase(trimmedText, "N/A") ||
            EqualsIgnoreCase(trimmedText, "nan"))
    {
        return false;
    }

    size_t currentPosition = 0;

    bool isNegativeNumber = false;

    if (trimmedText[currentPosition] == '-' || trimmedText[currentPosition] == '+')
    {
        isNegativeNumber = (trimmedText[currentPosition] == '-');
        ++currentPosition;
    }

    bool containsDigit = false;
    long long integerPartValue = 0;

    while (currentPosition < trimmedText.length() &&
            trimmedText[currentPosition] >= '0' &&
            trimmedText[currentPosition] <= '9')
    {
        containsDigit = true;
        integerPartValue = integerPartValue * 10 + (trimmedText[currentPosition] - '0');
        ++currentPosition;
    }

    double computedValue = static_cast<double>(integerPartValue);

    if (currentPosition < trimmedText.length() && trimmedText[currentPosition] == '.')
    {
        ++currentPosition;

        double decimalPlaceMultiplier = 0.1;

        while (currentPosition < trimmedText.length() &&
                trimmedText[currentPosition] >= '0' &&
                trimmedText[currentPosition] <= '9')
        {
            containsDigit = true;
            computedValue += (trimmedText[currentPosition] - '0') * decimalPlaceMultiplier;
            decimalPlaceMultiplier *= 0.1;
            ++currentPosition;
        }
    }

    while (currentPosition < trimmedText.length() &&
            IsWhitespaceCharacter(trimmedText[currentPosition]))
    {
        ++currentPosition;
    }

    if (!containsDigit || currentPosition != trimmedText.length())
    {
        return false;
    }

    if (isNegativeNumber)
    {
        computedValue = -computedValue;
    }

    outputValue = static_cast<float>(computedValue);
    return true;
}

//----------------------------------------------------------------------------
// Parses dd/mm/yyyy into a Date object.
static bool ParseDateDayMonthYear(const std::string& dateText, Date& dateObject)
{
    size_t currentPosition = 0;

    int dayValue = 0;
    int monthValue = 0;
    int yearValue = 0;

    if (!ParseIntegerValue(dateText, currentPosition, dayValue))
    {
        return false;
    }

    if (currentPosition >= dateText.length() || dateText[currentPosition] != '/')
    {
        return false;
    }
    ++currentPosition;

    if (!ParseIntegerValue(dateText, currentPosition, monthValue))
    {
        return false;
    }

    if (currentPosition >= dateText.length() || dateText[currentPosition] != '/')
    {
        return false;
    }
    ++currentPosition;

    if (!ParseIntegerValue(dateText, currentPosition, yearValue))
    {
        return false;
    }

    dateObject.SetYear(yearValue);
    dateObject.SetMonth(monthValue);
    dateObject.SetDay(dayValue);

    return true;
}

//----------------------------------------------------------------------------
// Parses HH:MM or HH:MM:SS into a Time object.
static bool ParseTimeHourMinuteSecond(const std::string& timeText, Time& timeObject)
{
    size_t currentPosition = 0;

    int hourValue = 0;
    int minuteValue = 0;
    int secondValue = 0;

    if (!ParseIntegerValue(timeText, currentPosition, hourValue))
    {
        return false;
    }

    if (currentPosition >= timeText.length() || timeText[currentPosition] != ':')
    {
        return false;
    }
    ++currentPosition;

    if (!ParseIntegerValue(timeText, currentPosition, minuteValue))
    {
        return false;
    }

    if (currentPosition < timeText.length() && timeText[currentPosition] == ':')
    {
        ++currentPosition;
        if (!ParseIntegerValue(timeText, currentPosition, secondValue))
        {
            return false;
        }
    }

    timeObject.SetHour(hourValue);
    timeObject.SetMinute(minuteValue);
    timeObject.SetSecond(secondValue);

    return true;
}

//----------------------------------------------------------------------------
// Attempts to open a file as-is, then with a data/ prefix.
static bool OpenFileWithFallback(const std::string& filePath, std::ifstream& inputStream)
{
    inputStream.open(filePath.c_str());
    if (inputStream.is_open())
    {
        return true;
    }

    inputStream.clear();

    std::string prefixedPath = "data/" + filePath;
    inputStream.open(prefixedPath.c_str());
    return inputStream.is_open();
}

//----------------------------------------------------------------------------
// Loads a single CSV file into the log.
static int LoadSingleCsvFileIntoLog(const std::string& csvFilePath, WeatherLogType& log)
{
    std::ifstream csvFileStream;
    if (!OpenFileWithFallback(csvFilePath, csvFileStream))
    {
        std::cout << "Error: Could not open " << csvFilePath << "\n";
        return 0;
    }

    std::string headerLine;
    if (!std::getline(csvFileStream, headerLine))
    {
        std::cout << "Error: Empty file " << csvFilePath << "\n";
        csvFileStream.close();
        return 0;
    }

    char delimiterCharacter = DetectDelimiterCharacter(headerLine);

    int dateTimeColumnIndex = FindColumnIndex(headerLine, "WAST");
    int windSpeedColumnIndex = FindColumnIndex(headerLine, "S");
    int solarRadiationColumnIndex = FindColumnIndex(headerLine, "SR");
    int temperatureColumnIndex = FindColumnIndex(headerLine, "T");

    if (dateTimeColumnIndex == -1)
    {
        std::cout << "ERROR: WAST column missing in " << csvFilePath << "\n";
        csvFileStream.close();
        return 0;
    }

    int loadedRecordCount = 0;
    std::string dataLine;

    while (std::getline(csvFileStream, dataLine))
    {
        if (Trim(dataLine).empty())
        {
            continue;
        }

        std::string dateTimeCell = ExtractFieldByColumnIndex(dataLine, dateTimeColumnIndex, delimiterCharacter);
        if (dateTimeCell.empty())
        {
            continue;
        }

        size_t spacePosition = dateTimeCell.find(' ');
        if (spacePosition == std::string::npos)
        {
            continue;
        }

        std::string dateText = dateTimeCell.substr(0, spacePosition);
        std::string timeText = Trim(dateTimeCell.substr(spacePosition + 1));

        Date dateObject;
        Time timeObject;

        if (!ParseDateDayMonthYear(dateText, dateObject))
        {
            continue;
        }

        if (!ParseTimeHourMinuteSecond(timeText, timeObject))
        {
            continue;
        }

        float windSpeedValue = -1.0f;
        float solarRadiationValue = -1.0f;
        float temperatureValue = -1.0f;

        if (windSpeedColumnIndex != -1)
        {
            float parsedValue = 0.0f;
            if (ParseFloatingPointValue(ExtractFieldByColumnIndex(dataLine, windSpeedColumnIndex, delimiterCharacter), parsedValue))
            {
                windSpeedValue = parsedValue;
            }
        }

        if (solarRadiationColumnIndex != -1)
        {
            float parsedValue = 0.0f;
            if (ParseFloatingPointValue(ExtractFieldByColumnIndex(dataLine, solarRadiationColumnIndex, delimiterCharacter), parsedValue))
            {
                solarRadiationValue = parsedValue;
            }
        }

        if (temperatureColumnIndex != -1)
        {
            float parsedValue = 0.0f;
            if (ParseFloatingPointValue(ExtractFieldByColumnIndex(dataLine, temperatureColumnIndex, delimiterCharacter), parsedValue))
            {
                temperatureValue = parsedValue;
            }
        }

        WeatherRecType weatherRecord(dateObject, timeObject, windSpeedValue, temperatureValue, solarRadiationValue);
        log.AddRecord(weatherRecord);
        ++loadedRecordCount;
    }

    csvFileStream.close();
    std::cout << "Successfully loaded " << loadedRecordCount << " records from " << csvFilePath << "\n";
    return loadedRecordCount;
}

//----------------------------------------------------------------------------
// Main API: load from config list (one filename per line).
void WeatherFileReader::LoadFromConfig(WeatherLogType& log, const std::string& configPath)
{
    std::ifstream configFileStream;
    configFileStream.open(configPath.c_str());

    if (!configFileStream.is_open() && configPath == "data/data_source.txt")
    {
        configFileStream.clear();
        configFileStream.open("data_source.txt");
    }

    if (!configFileStream.is_open())
    {
        std::cout << "Error: Could not open " << configPath << " (or data_source.txt)\n";
        return;
    }

    std::string csvFilePath;

    while (std::getline(configFileStream, csvFilePath))
    {
        csvFilePath = Trim(csvFilePath);

        if (csvFilePath.empty())
        {
            continue;
        }

        LoadSingleCsvFileIntoLog(csvFilePath, log);
    }

    configFileStream.close();
}
