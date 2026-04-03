// MenuHandlerTest_UPDATED.cpp
//
// Unit test for MenuHandler (interactive).
//
// Version
// 02 01/03/2026 Heng Kiao Woon
//---------------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Includes
#include "Menu.h"
#include "MenuHandler.h"
#include "WeatherFileReader.h"
#include "WeatherLogType.h"
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

    // Header must include WAST, S, SR, T
    outputFile << "WAST,S,SR,T\n";
    outputFile << "31/03/2016 09:00,6,512,22.7\n";
    outputFile << "31/03/2016 09:10,5,565,22.7\n";
    outputFile << "31/03/2016 09:20,5,574,22.7\n";

    outputFile.close();
    return true;
}

//----------------------------------------------------------------------------
// Writes a config file listing the CSV file path (one per line).
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
// Program entry point
int main()
{
    std::cout << "===== MenuHandlerTest =====\n\n";

    const std::string csvFilePath = "TestMetData.csv";
    const std::string configFilePath = "TestDataSource.txt";

    std::cout << "-- Test 1 (Prepare sample data files) --\n";

    if (!WriteSampleCsvFile(csvFilePath))
    {
        std::cout << "ERROR: Failed to write CSV file: " << csvFilePath << "\n";
        return 1;
    }

    if (!WriteConfigFile(configFilePath, csvFilePath))
    {
        std::cout << "ERROR: Failed to write config file: " << configFilePath << "\n";
        return 1;
    }

    std::cout << "Created test CSV and config files.\n\n";

    std::cout << "-- Test 2 (Load weather data) --\n";
    WeatherLogType weatherLog;
    WeatherFileReader weatherFileReader;
    weatherFileReader.LoadFromConfig(weatherLog, configFilePath);

    std::cout << "WeatherLogType size after loading: " << weatherLog.GetSize() << "\n\n";

    std::cout << "-- Test 3 (Run MenuHandler) --\n";
    std::cout << "IMPORTANT: To see data, choose:\n";
    std::cout << "  Month = 3\n";
    std::cout << "  Year  = 2016\n";
    std::cout << "Wind expected (small dataset): Mean ~ 5.33333, Sample stdev ~ 0.57735\n";
    std::cout << "To end this test, choose option 5 (Quit).\n\n";

    Menu menu;
    MenuHandler menuHandler(menu, weatherLog);
    menuHandler.Run();

    std::cout << "\nProcess completed.\n";
    return 0;
}
