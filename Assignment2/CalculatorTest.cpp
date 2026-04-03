// CalculatorTest.cpp
//
// Console test program for Calculator helper functions.
// Exercises mean and standard deviation routines using simple test data.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Unit Test for Calculator.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Calculator.h"
#include <iostream>

//----------------------------------------------------------------------------
// Runs unit tests for Calculator functions
int main()
{
    std::cout << "===== CalculatorTest =====" << std::endl << std::endl;

    float values[] = {10, 20, 30, 40, 50};
    int size = 5;

    std::cout << "-- Test 1 (Mean) --" << std::endl;
    float mean = calculateMean(values, size);
    std::cout << "Mean = " << mean << std::endl << std::endl;

    std::cout << "-- Test 2 (Standard Deviation) --" << std::endl;
    float stdev = calculateStandardDeviation(values, size);
    std::cout << "Standard deviation = " << stdev << std::endl << std::endl;

    return 0;
}
