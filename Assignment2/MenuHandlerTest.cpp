//
// MenuHandlerTest.cpp
//
// Console integration test program for MenuHandler.
// Loads sample weather data and runs the menu controller against known input files.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Unit Test for MenuHandler.
// 02 03/04/2026 Heng Kiao Woon - Updated file header, removed WeatherLogType.
// 03 04/04/2026 Heng Kiao Woon - Refactored test for WeatherBstMapStore and MenuHandler.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Menu.h"
#include "MenuHandler.h"
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
    outputFile << "31/03/2016 09:10,5,565,23.0\n";
    outputFile << "31/03/2016 09:20,5,574,22.4\n";
    outputFile << "01/04/2016 09:00,4,480,21.1\n";

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
    std::cout << "===== MenuHandlerTest =====\n\n";

    const std::string csvFilePath = "data/TestMetData.csv";
    const std::string configFilePath = "data/TestDataSource.txt";

    std::cout << "-- Test 1: Prepare sample data files --\n";

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

    std::cout << "-- Test 2: Load data into WeatherBstMapStore --\n";

    WeatherBstMapStore store;
    WeatherFileReader weatherFileReader;

    // Assumption:
    // Your WeatherFileReader should have an overload similar to:
    // weatherFileReader.LoadFromConfig(configFilePath, store);
    //
    // If your actual function name/signature is different, adjust this line only.
    weatherFileReader.LoadFromConfig(configFilePath, store);

    std::cout << "Data load completed.\n\n";

    std::cout << "-- Test 3: Run MenuHandler --\n";
    std::cout << "Recommended manual checks:\n";
    std::cout << "1. Option 1 -> Month 3, Year 2016\n";
    std::cout << "   Expected wind mean = 5.33333 m/s = about 19.2 km/h\n";
    std::cout << "   Expected sample stdev = 0.57735 m/s = about 2.07846 km/h\n";
    std::cout << "2. Option 2 -> Year 2016\n";
    std::cout << "   March and April should show data.\n";
    std::cout << "3. Option 3 -> Month 3\n";
    std::cout << "   Should print S_T, S_R, and T_R across all loaded years for March.\n";
    std::cout << "4. Option 4 -> Year 2016\n";
    std::cout << "   Should create WindTempSolar.csv\n";
    std::cout << "5. Option 5 -> Exit\n\n";

    Menu menu;
    MenuHandler menuHandler(menu, store);
    menuHandler.Run();

    std::cout << "\nProcess completed.\n";
    return 0;
}
