// CalculatorTest.cpp
//
// Console test program for Calculator helper functions.
// Exercises mean, standard deviation and sPCC using Vectir test data.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Unit Test for Calculator.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
// 03 03/04/2026 Heng Kiao Woon - Updated tests to use Vector and added sPCC tests.
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

    Vector<float> values;
    values.Add(10.0f);
    values.Add(20.0f);
    values.Add(30.0f);
    values.Add(40.0f);
    values.Add(50.0f);

    std::cout << "-- Test 1 (Mean) --" << std::endl;
    float mean = calculateMean(values);
    std::cout << "Mean = " << mean << std::endl << std::endl;

    std::cout << "-- Test 2 (Standard Deviation) --" << std::endl;
    float stdev = calculateStandardDeviation(values);
    std::cout << "Standard deviation = " << stdev << std::endl << std::endl;

    Vector<float> xValues;
    xValues.Add(1.0f);
    xValues.Add(2.0f);
    xValues.Add(3.0f);
    xValues.Add(4.0f);
    xValues.Add(5.0f);

    Vector<float> yValues;
    yValues.Add(2.0f);
    yValues.Add(4.0f);
    yValues.Add(6.0f);
    yValues.Add(8.0f);
    yValues.Add(10.0f);

    std::cout << "-- Test 3 (sPCC) --" << std::endl;
    float correlation = sPCC(xValues, yValues);
    std::cout << "sPCC = " << correlation << std::endl << std::endl;

    std::cout << "-- Test 4 (MAD) --" << std::endl;
    float meanAbsoluteDeviation = mad(values);
    std::cout << "MAD = " << meanAbsoluteDeviation << std::endl << std::endl;

    return 0;
}
