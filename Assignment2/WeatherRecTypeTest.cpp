// WeatherRecTypeTest.cpp
//
// Unit test for WeatherRecType.
// Demonstrates constructors and getter methods.
//
// Version
// 02 01/03/2026 Heng Kiao Woon
//---------------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Includes
#include "WeatherRecType.h"
#include <iostream>

//----------------------------------------------------------------------------
// Program entry point
int main()
{
    std::cout << "===== WeatherRecTypeTest =====\n\n";

    std::cout << "-- Test 1 (Default constructor) --\n";
    WeatherRecType defaultRecord;
    std::cout << "Default record created.\n";
    std::cout << "Speed: " << defaultRecord.GetSpeed() << "\n";
    std::cout << "Temperature: " << defaultRecord.GetAmbientTemperature() << "\n";
    std::cout << "Solar Radiation: " << defaultRecord.GetSolarRadiation() << "\n\n";

    std::cout << "-- Test 2 (Parameterized constructor + getters) --\n";
    Date dateObject(31, 3, 2016);
    Time timeObject(9, 10, 0);

    float windSpeedValue = 5.5f;
    float ambientTemperatureValue = 22.7f;
    float solarRadiationValue = 512.0f;

    WeatherRecType parameterizedRecord(dateObject,
                                      timeObject,
                                      windSpeedValue,
                                      ambientTemperatureValue,
                                      solarRadiationValue);

    std::cout << "Parameterized record created.\n";
    std::cout << "Speed: " << parameterizedRecord.GetSpeed() << "\n";
    std::cout << "Temperature: " << parameterizedRecord.GetAmbientTemperature() << "\n";
    std::cout << "Solar Radiation: " << parameterizedRecord.GetSolarRadiation() << "\n\n";

    std::cout << "\nProcess completed.\n";
    return 0;
}
