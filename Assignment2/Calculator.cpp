//
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
// 04 04/04/2026 Heng Kiao Woon - Fixed float comparison in sPCC.
//---------------------------------------------------------------------------------

#include "Calculator.h"

float absoluteValue(float value)
{
    if (value < 0.0f)
        return -value;
    return value;
}

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
    const float epsilon = 0.000001f;

    if (absoluteValue(denominator) < epsilon)
        return 0.0f;

    return numerator / denominator;
}

float mad(const Vector<float>& dataVector)
{
    int n = dataVector.Size();

    if (n <= 0)
        return 0.0f;

    float mean = calculateMean(dataVector);
    float sumAbsoluteDeviation = 0.0f;

    for (int i = 0; i < n; ++i)
    {
        sumAbsoluteDeviation += absoluteValue(dataVector[i] - mean);
    }

    return sumAbsoluteDeviation / static_cast<float>(n);
}

float ConvertMsToKmh(float ms)
{
    return ms * 3.6f;
}
