// TimeTest.cpp
//
// Console test program for the Time class.
// Checks construction, validation, setters, getters,
// stream output behaviour, and comparison operators.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Unit Test for Time.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
// 03 03/04/2026 Heng Kiao Woon - Added comparison operator tests.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Time.h"
#include <iostream>

//----------------------------------------------------------------------------
// Runs unit tests for Time class
int main()
{
    std::cout << "===== TimeTest =====" << std::endl << std::endl;

    std::cout << "-- Test 1 (Default constructor) --" << std::endl;
    Time t1;
    std::cout << "t1 = " << t1 << std::endl << std::endl;

    std::cout << "-- Test 2 (Parameterized constructor) --" << std::endl;
    Time t2(9, 10);
    std::cout << "t2 = " << t2 << std::endl << std::endl;

    std::cout << "-- Test 3 (Full parameter constructor) --" << std::endl;
    Time t3(23, 59, 58);
    std::cout << "t3 = " << t3 << std::endl << std::endl;

    std::cout << "-- Test 4 (Invalid values) --" << std::endl;
    Time t4(99, -1, 77);
    std::cout << "t4 = " << t4 << std::endl << std::endl;

    std::cout << "-- Test 5 (Setters and Getters) --" << std::endl;
    Time t5;
    t5.SetHour(12);
    t5.SetMinute(30);
    t5.SetSecond(45);

    std::cout << "t5 = " << t5 << std::endl;
    std::cout << "Hour=" << t5.GetHour()
              << " Min=" << t5.GetMinute()
              << " Sec=" << t5.GetSecond()
              << std::endl << std::endl;

    std::cout << "-- Test 6 (Comparison operators) --" << std::endl;
    Time a(9, 15, 0);
    Time b(10, 0, 0);
    Time c(9, 15, 0);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;

    std::cout << "a == c: " << (a == c) << std::endl;
    std::cout << "a != b: " << (a != b) << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;
    std::cout << "b > a: " << (b > a) << std::endl;
    std::cout << "a <= c: " << (a <= c) << std::endl;
    std::cout << "b >= a: " << (b >= a) << std::endl;
    std::cout << std::endl;

    return 0;
}
