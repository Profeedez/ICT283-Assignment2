// Calculator.cpp
//
// Mathematical helper function implementations used by the weather statistics program.
// Implements absolute value, square root, mean, standard deviation, and wind-speed conversion routines.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial Calculator implementation
// 02 03/04/2026 Heng Kiao Woon - Updated file header
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Calculator.h"

//----------------------------------------------------------------------------
// Function implementations

//----------------------------------------------------------------------------
// Returns the absolute (non-negative) value of a float.
float absoluteValue(float value)
{
    if (value < 0.0f)
        return -value;
    return value;
}

//----------------------------------------------------------------------------
// Computes the square root of x using Newton's method (iterative approximation).
float squareRoot(float x)
{
    if (x <= 0.0f)
        return 0.0f;

    float guess = x;

    for (int i = 0; i < 50; i++)
    {
        float next = 0.5f * (guess + x / guess);

        if (absoluteValue(next - guess) < 0.00001f)
            return next;

        guess = next;
    }

    return guess;
}

//----------------------------------------------------------------------------
// Calculates the arithmetic mean of an array of floats.
float calculateMean(const float dataArray[], int n)
{
    if (n <= 0 || dataArray == nullptr) return 0.0f;
    float sum = 0.0f;
    for (int i = 0; i < n; i++)
    {
        sum += dataArray[i];
    }
    return sum / static_cast<float>(n);
}

//----------------------------------------------------------------------------
// Calculates the standard deviation (n-1) of an array of floats.
float calculateStandardDeviation(const float dataArray[], int n)
{
    if (dataArray == nullptr || n <= 1)
        return 0.0f;

    // Step 1: calculate mean
    float sum = 0.0f;
    for (int i = 0; i < n; i++)
        sum += dataArray[i];

    float mean = sum / n;

    // Step 2: sum of squared differences
    float sumSq = 0.0f;
    for (int i = 0; i < n; i++)
    {
        float diff = dataArray[i] - mean;
        sumSq += diff * diff;
    }

    // Step 3: divide by (n - 1)  → standard deviation
    float variance = sumSq / (n - 1);

    // Step 4: square root
    return squareRoot(variance);
}

//----------------------------------------------------------------------------
// Converts metres/second to kilometres/hour.
float ConvertMsToKmh(float ms)
{
    return ms * 3.6f;
}
