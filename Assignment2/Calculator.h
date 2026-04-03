/**
 * @file Calculator.h
 * @brief Declares mathematical helper functions used by the weather statistics program.
 *
 * This file provides small calculation utilities used throughout the project,
 * including absolute value, Newton's method square root, arithmetic mean,
 * standard deviation, and wind-speed unit conversion.
 *
 * @author Heng Kiao Woon
 * @version 02
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial creation for Assignment 1.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header

#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

/**
 * @brief Returns the absolute value of @p value.
 * @param value Input value.
 * @return |value|.
 */
float absoluteValue(float value);

/**
 * @brief Computes the square root of @p x using Newton's method.
 * @param x Value to square-root.
 * @return sqrt(x). Returns 0 if x <= 0.
 */
float squareRoot(float x);

/**
 * @brief Calculates the arithmetic mean of @p dataArray.
 * @param dataArray The array of values.
 * @param n The number of elements in the array.
 * @return The mean value. If n <= 0, implementations typically return 0.
 */
float calculateMean(const float dataArray[], int n);

/**
 * @brief Calculates the sample standard deviation of @p dataArray.
 * @param dataArray Array of float values.
 * @param n Number of elements.
 * @return Sample standard deviation.
 *
 * Formula:
 *   s = sqrt( sum((x - mean)^2) / (n - 1) )
 */
float calculateStandardDeviation(const float dataArray[], int n);

/**
 * @brief Converts speed from meters per second to kilometers per hour.
 * @param ms Speed in m/s.
 * @return Speed in km/h (ms * 3.6).
 */
float ConvertMsToKmh(float ms);

#endif // CALCULATOR_H_INCLUDED
