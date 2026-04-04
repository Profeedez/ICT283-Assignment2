//
// WeatherFileReaderTest.cpp
//
// Console test program for WeatherFileReader.
// Creates sample files and verifies that weather data can be loaded into the program model.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Unit Test for WeatherFileReader.
// 02 03/04/2026 Heng Kiao Woon - Updated file header, removed WeatherLogType.
// 03 04/04/2026 Heng Kiao Woon - Refactored test for WeatherBstMapStore.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "WeatherFileReader.h"
#include "WeatherBstMapStore.h"
#include <fstream>
#include <iostream>
#include <string>

//----------------------------------------------------------------------------
// Writes a small sample CSV file compatible with WeatherFileReader.
static bool WriteSampleCsvFile(const std::string& csvFilePath)
{
    std::ofstream outputFile(csvFilePath.c_str());
    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << "WAST,S,SR,T\n";
    outputFile << "31/03/2016 09:00,6,512,22.7\n";
    outputFile << "31/03/2016 09:10,5,565,22.9\n";
    outputFile << "31/03/2016 09:20,5,574,22.4\n";
    outputFile << "01/04/2016 09:00,4,480,21.1\n";
    outputFile << "01/04/2016 09:10,N/A,490,21.5\n";

    outputFile.close();
    return true;
}

//----------------------------------------------------------------------------
// Writes a config file listing the CSV file path.
static bool WriteConfigFile(const std::string& configFilePath,
                            const std::string& csvFilePath)
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
// Program entry point.
int main()
{
    std::cout << "===== WeatherFileReaderTest =====\n\n";

    const std::string csvFilePath = "data/TestMetData.csv";
    const std::string configFilePath = "data/TestDataSource.txt";

    std::cout << "-- Test 1: Create sample CSV and config files --\n";

    if (!WriteSampleCsvFile(csvFilePath))
    {
        std::cout << "FAIL: Could not create sample CSV file.\n";
        return 1;
    }

    if (!WriteConfigFile(configFilePath, csvFilePath))
    {
        std::cout << "FAIL: Could not create config file.\n";
        return 1;
    }

    std::cout << "PASS: Sample files created successfully.\n\n";

    std::cout << "-- Test 2: Load records into WeatherBstMapStore --\n";

    WeatherBstMapStore store;
    WeatherFileReader reader;
    reader.LoadFromConfig(configFilePath, store);

    std::cout << "PASS: LoadFromConfig executed.\n\n";

    std::cout << "-- Test 3: Verify March 2016 data exists --\n";
    std::cout << "HasValidWind(3, 2016): "
              << store.HasValidWind(3, 2016) << "\n";
    std::cout << "HasValidTemperature(3, 2016): "
              << store.HasValidTemperature(3, 2016) << "\n";
    std::cout << "HasValidSolar(3, 2016): "
              << store.HasValidSolar(3, 2016) << "\n\n";

    std::cout << "-- Test 4: Verify April 2016 data exists --\n";
    std::cout << "HasValidWind(4, 2016): "
              << store.HasValidWind(4, 2016) << "\n";
    std::cout << "HasValidTemperature(4, 2016): "
              << store.HasValidTemperature(4, 2016) << "\n";
    std::cout << "HasValidSolar(4, 2016): "
              << store.HasValidSolar(4, 2016) << "\n\n";

    std::cout << "-- Test 5: Check calculated values --\n";

    if (store.HasValidWind(3, 2016))
    {
        std::cout << "March 2016 wind mean (m/s): "
                  << store.FindSpeedMean(3, 2016) << "\n";
        std::cout << "March 2016 wind sample stdev (m/s): "
                  << store.FindSpeedStandardDeviation(3, 2016) << "\n";
    }

    if (store.HasValidTemperature(3, 2016))
    {
        std::cout << "March 2016 temperature mean: "
                  << store.FindTemperatureMean(3, 2016) << "\n";
        std::cout << "March 2016 temperature sample stdev: "
                  << store.FindTemperatureStandardDeviation(3, 2016) << "\n";
    }

    if (store.HasValidSolar(3, 2016))
    {
        std::cout << "March 2016 total solar radiation: "
                  << store.FindTotalSolar(3, 2016) << "\n";
    }

    std::cout << "\nExpected observations:\n";
    std::cout << "- March 2016 should contain valid wind, temperature, and solar data.\n";
    std::cout << "- April 2016 should also contain valid temperature and solar data.\n";
    std::cout << "- The 'N/A' wind value should not crash parsing.\n\n";

    std::cout << "WeatherFileReaderTest completed.\n";
    return 0;
}
