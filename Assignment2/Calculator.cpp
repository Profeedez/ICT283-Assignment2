// Calculator.cpp
//
// Mathematical helper function implementations used by the weather statistics program.
// Implements absolute value, square root, mean, standard deviation, sPCC,
// and wind-speed conversion routines.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial Calculator implementation.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
// 03 03/04/2026 Heng Kiao Woon - Refactored statistical functions to use Vector.
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
// Calculates the arithmetic mean of a vector of floats.
float calculateMean(const Vector<float>& dataVector)
{
    if (dataVector.Size() <= 0)
        return 0.0f;

    float sum = 0.0f;

    for (int i = 0; i < dataVector.Size(); ++i)
    {
        sum += dataVector[i];
    }

    return sum / static_cast<float>(dataVector.Size());
}

//----------------------------------------------------------------------------
// Calculates the sample standard deviation (n-1) of a vector of floats.
float calculateStandardDeviation(const Vector<float>& dataVector)
{
    int n = dataVector.Size();

    if (n <= 1)
        return 0.0f;

    float mean = calculateMean(dataVector);
    float sumSq = 0.0f;

    for (int i = 0; i < n; ++i)
    {
        float diff = dataVector[i] - mean;
        sumSq += diff * diff;
    }

    float variance = sumSq / static_cast<float>(n - 1);
    return squareRoot(variance);
}

//----------------------------------------------------------------------------
// Calculates the sample Pearson Correlation Coefficient between two vectors.
float sPCC(const Vector<float>& x, const Vector<float>& y)
{
    int n = x.Size();

    if (n != y.Size() || n <= 1)
        return 0.0f;

    float meanX = calculateMean(x);
    float meanY = calculateMean(y);

    float numerator = 0.0f;
    float sumSqX = 0.0f;
    float sumSqY = 0.0f;

    for (int i = 0; i < n; ++i)
    {
        float diffX = x[i] - meanX;
        float diffY = y[i] - meanY;

        numerator += diffX * diffY;
        sumSqX += diffX * diffX;
        sumSqY += diffY * diffY;
    }

    float denominator = squareRoot(sumSqX * sumSqY);

    if (denominator == 0.0f)
        return 0.0f;

    return numerator / denominator;
}

//----------------------------------------------------------------------------
// Converts metres/second to kilometres/hour.
float ConvertMsToKmh(float ms)
{
    return ms * 3.6f;
}
