// WeatherRecTypeTest.cpp
//
// Console test program for the WeatherRecType class.
// Checks construction, stored measurement values,
// and comparison operators for timestamp ordering.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Unit Test for WeatherRecType.
// 02 01/03/2026 Heng Kiao Woon - Expanded constructor and getter checks.
// 03 03/04/2026 Heng Kiao Woon - Updated file header.
// 04 03/04/2026 Heng Kiao Woon - Added comparison operator tests.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "WeatherRecType.h"
#include <iostream>

//----------------------------------------------------------------------------
// Program entry point
int main()
{
    std::cout << "===== WeatherRecTypeTest =====" << std::endl << std::endl;

    std::cout << "-- Test 1 (Default constructor) --" << std::endl;
    WeatherRecType defaultRecord;
    std::cout << "Default record created." << std::endl;
    std::cout << "Speed: " << defaultRecord.GetSpeed() << std::endl;
    std::cout << "Temperature: " << defaultRecord.GetAmbientTemperature() << std::endl;
    std::cout << "Solar Radiation: " << defaultRecord.GetSolarRadiation() << std::endl << std::endl;

    std::cout << "-- Test 2 (Parameterized constructor + getters) --" << std::endl;
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

    std::cout << "Parameterized record created." << std::endl;
    std::cout << "Speed: " << parameterizedRecord.GetSpeed() << std::endl;
    std::cout << "Temperature: " << parameterizedRecord.GetAmbientTemperature() << std::endl;
    std::cout << "Solar Radiation: " << parameterizedRecord.GetSolarRadiation() << std::endl << std::endl;

    std::cout << "-- Test 3 (Comparison operators) --" << std::endl;
    WeatherRecType recordA(Date(1, 4, 2016), Time(9, 0, 0), 5.0f, 21.0f, 400.0f);
    WeatherRecType recordB(Date(1, 4, 2016), Time(10, 0, 0), 6.0f, 22.0f, 420.0f);
    WeatherRecType recordC(Date(1, 4, 2016), Time(9, 0, 0), 7.0f, 23.0f, 440.0f);

    std::cout << "recordA timestamp = "
              << recordA.GetDate() << " " << recordA.GetTime() << std::endl;
    std::cout << "recordB timestamp = "
              << recordB.GetDate() << " " << recordB.GetTime() << std::endl;
    std::cout << "recordC timestamp = "
              << recordC.GetDate() << " " << recordC.GetTime() << std::endl;

    std::cout << "recordA == recordC: " << (recordA == recordC) << std::endl;
    std::cout << "recordA != recordB: " << (recordA != recordB) << std::endl;
    std::cout << "recordA < recordB: " << (recordA < recordB) << std::endl;
    std::cout << "recordB > recordA: " << (recordB > recordA) << std::endl;
    std::cout << "recordA <= recordC: " << (recordA <= recordC) << std::endl;
    std::cout << "recordB >= recordA: " << (recordB >= recordA) << std::endl;
    std::cout << std::endl;

    std::cout << "Process completed." << std::endl;
    return 0;
}
