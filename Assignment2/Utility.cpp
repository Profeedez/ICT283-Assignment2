// Utility.cpp
//
// Shared helper function implementations used across the project.
// Includes string trimming, month conversion, CSV header lookup, and input validation support.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial Utility implementation.
// 02 01/03/2026 Heng Kiao Woon - Expanded parsing and formatting helpers.
// 03 01/03/2026 Heng Kiao Woon - Added validated integer input support.
// 04 03/04/2026 Heng Kiao Woon - Updated file header.
//---------------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Includes
#include "Utility.h"
#include <iostream>

//----------------------------------------------------------------------------
// Checks whether a character is whitespace.
bool IsWhitespaceCharacter(char character)
{
    return (character == ' ' ||
            character == '\t' ||
            character == '\n' ||
            character == '\r');
}

//----------------------------------------------------------------------------
// Converts month number (1-12) to English month name.
std::string ConvertMonth(int monthNumber)
{
    switch (monthNumber)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    default:
        return "Unknown";
    }
}

//----------------------------------------------------------------------------
// Trims leading and trailing whitespace.
std::string Trim(const std::string& inputText)
{
    size_t startPosition = 0;

    while (startPosition < inputText.length() &&
            IsWhitespaceCharacter(inputText[startPosition]))
    {
        ++startPosition;
    }

    size_t endPosition = inputText.length();

    while (endPosition > startPosition &&
            IsWhitespaceCharacter(inputText[endPosition - 1]))
    {
        --endPosition;
    }

    return inputText.substr(startPosition, endPosition - startPosition);
}

//----------------------------------------------------------------------------
// Converts uppercase character to lowercase.
static char ConvertToLowercase(char character)
{
    if (character >= 'A' && character <= 'Z')
    {
        return static_cast<char>(character - 'A' + 'a');
    }

    return character;
}

//----------------------------------------------------------------------------
// Compares two strings ignoring case (ASCII only).
bool EqualsIgnoreCase(const std::string& firstText,
                      const std::string& secondText)
{
    if (firstText.length() != secondText.length())
    {
        return false;
    }

    for (size_t characterIndex = 0;
            characterIndex < firstText.length();
            ++characterIndex)
    {
        if (ConvertToLowercase(firstText[characterIndex]) !=
                ConvertToLowercase(secondText[characterIndex]))
        {
            return false;
        }
    }

    return true;
}

//----------------------------------------------------------------------------
// Detects delimiter in a header line.
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
// Finds zero-based column index for a column name.
int FindColumnIndex(const std::string& headerLine,
                    const std::string& columnName)
{
    char delimiterCharacter = DetectDelimiterCharacter(headerLine);

    int currentColumnIndex = 0;
    size_t startPosition = 0;

    while (startPosition <= headerLine.length())
    {
        size_t delimiterPosition =
            headerLine.find(delimiterCharacter, startPosition);

        std::string currentColumnValue;

        if (delimiterPosition == std::string::npos)
        {
            currentColumnValue = headerLine.substr(startPosition);
            startPosition = headerLine.length() + 1;
        }
        else
        {
            currentColumnValue =
                headerLine.substr(startPosition,
                                  delimiterPosition - startPosition);

            startPosition = delimiterPosition + 1;
        }

        currentColumnValue = Trim(currentColumnValue);

        if (!currentColumnValue.empty() &&
                currentColumnValue.back() == '\r')
        {
            currentColumnValue.pop_back();
        }

        if (EqualsIgnoreCase(currentColumnValue, columnName))
        {
            return currentColumnIndex;
        }

        ++currentColumnIndex;
    }

    return -1;
}

//----------------------------------------------------------------------------
// Parses integer manually (no sstream).
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
            (inputText[currentPosition] == '-' ||
             inputText[currentPosition] == '+'))
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

        numericValue =
            numericValue * 10 +
            (inputText[currentPosition] - '0');

        ++currentPosition;
    }

    if (!containsDigit)
    {
        return false;
    }

    if (isNegativeNumber)
    {
        numericValue = -numericValue;
    }

    outputValue = numericValue;
    return true;
}

//----------------------------------------------------------------------------
// Reads validated integer from user.
int GetValidInteger(const std::string& promptText,
                    int minimumValue,
                    int maximumValue)
{
    while (true)
    {
        std::cout << promptText;

        std::string inputText;
        std::getline(std::cin, inputText);

        inputText = Trim(inputText);

        if (inputText.empty())
        {
            std::cout << "Invalid input. Enter between "
                      << minimumValue << " and "
                      << maximumValue << ".\n";
            continue;
        }

        size_t currentPosition = 0;
        int parsedValue = 0;

        if (!ParseIntegerValue(inputText, currentPosition, parsedValue))
        {
            std::cout << "Invalid input. Enter between "
                      << minimumValue << " and "
                      << maximumValue << ".\n";
            continue;
        }

        while (currentPosition < inputText.length() &&
                IsWhitespaceCharacter(inputText[currentPosition]))
        {
            ++currentPosition;
        }

        if (currentPosition != inputText.length())
        {
            std::cout << "Invalid input. Enter between "
                      << minimumValue << " and "
                      << maximumValue << ".\n";
            continue;
        }

        if (parsedValue < minimumValue || parsedValue > maximumValue)
        {
            std::cout << "Invalid input. Enter between "
                      << minimumValue << " and "
                      << maximumValue << ".\n";
            continue;
        }

        return parsedValue;
    }
}
