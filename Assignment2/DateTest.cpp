// DateTest.cpp
//
// Console test program for the Date class.
// Checks construction, validation, setters, getters, and stream output behaviour.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Unit test for Date.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Date.h"
#include <iostream>

//----------------------------------------------------------------------------
// Runs unit tests for Date class
int main()
{
    std::cout << "===== DateTest =====" << std::endl << std::endl;

    std::cout << "-- Test 1 (Default constructor) --" << std::endl;
    Date d1;
    std::cout << "d1 = " << d1 << std::endl << std::endl;

    std::cout << "-- Test 2 (Parameterized constructor) --" << std::endl;
    Date d2(31, 3, 2016);
    std::cout << "d2 = " << d2 << std::endl << std::endl;

    std::cout << "-- Test 3 (Invalid day validation) --" << std::endl;
    Date d3(31, 4, 2016);
    std::cout << "d3 = " << d3 << std::endl << std::endl;

    std::cout << "-- Test 4 (Setters) --" << std::endl;
    Date d4;
    d4.SetYear(2020);
    d4.SetMonth(2);
    d4.SetDay(29);
    std::cout << "d4 after set: " << d4 << std::endl << std::endl;

    std::cout << "-- Test 5 (Getters) --" << std::endl;
    std::cout << "Day=" << d2.GetDay()
              << " Month=" << d2.GetMonth()
              << " Year=" << d2.GetYear()
              << std::endl << std::endl;

    return 0;
}
