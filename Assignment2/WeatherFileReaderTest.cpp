// WeatherFileReaderTest.cpp
//
// Unit test for WeatherFileReader.
// This test writes a small CSV file and a config file at runtime,
// then loads the data into WeatherLogType.
//
// Version
// 01 01/03/2026 Heng Kiao Woon
//---------------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Includes
#include "WeatherFileReader.h"
#include "WeatherLogType.h"
#include <fstream>
#include <iostream>

//----------------------------------------------------------------------------
// Writes a small sample CSV file compatible with WeatherFileReader.
static bool WriteSampleCsvFile(const std::string& csvFilePath)
{
    std::ofstream outputFile(csvFilePath.c_str());
    if (!outputFile.is_open())
    {
        return false;
    }

    // Header must include WAST, S, SR, T (tab-delimited in this sample)
    outputFile << "WAST\tS\tSR\tT\n";
    outputFile << "31/03/2016 09:00\t6\t512\t22.7\n";
    outputFile << "31/03/2016 09:10\t5\t565\t22.7\n";
    outputFile << "31/03/2016 09:20\t5\t574\t22.7\n";

    outputFile.close();
    return true;
}

//----------------------------------------------------------------------------
// Writes a config file listing the CSV file path (one per line).
static bool WriteConfigFile(const std::string& configFilePath, const std::string& csvFilePath)
{
    std::ofstream outputFile(configFilePath.c_str());
    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << csvFilePath << "\n";
    outputFile.close();
    return true;
}

//----------------------------------------------------------------------------
// Program entry point
int main()
{
    std::cout << "===== WeatherFileReaderTest =====\n\n";

    const std::string csvFilePath = "TestMetData.csv";
    const std::string configFilePath = "TestDataSource.txt";

    std::cout << "-- Test 1 (Prepare test files) --\n";
    if (!WriteSampleCsvFile(csvFilePath))
    {
        std::cout << "Failed to write CSV file: " << csvFilePath << "\n";
        return 1;
    }

    if (!WriteConfigFile(configFilePath, csvFilePath))
    {
        std::cout << "Failed to write config file: " << configFilePath << "\n";
        return 1;
    }

    std::cout << "Created test CSV and config files.\n\n";

    std::cout << "-- Test 2 (LoadFromConfig) --\n";
    WeatherLogType weatherLog;
    WeatherFileReader weatherFileReader;

    weatherFileReader.LoadFromConfig(weatherLog, configFilePath);

    std::cout << "WeatherLogType size after loading: " << weatherLog.GetSize() << "\n";

    if (weatherLog.GetSize() == 0)
    {
        std::cout << "ERROR: No records loaded.\n";
        return 1;
    }

    std::cout << "First record wind speed: " << weatherLog[0].GetSpeed() << "\n";
    std::cout << "First record solar radiation: " << weatherLog[0].GetSolarRadiation() << "\n";
    std::cout << "First record temperature: " << weatherLog[0].GetAmbientTemperature() << "\n";

    std::cout << "\nProcess completed.\n";
    return 0;
}
