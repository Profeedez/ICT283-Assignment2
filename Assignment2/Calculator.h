/**
 * @file Calculator.h
 * @brief Declares mathematical helper functions used by the weather statistics program.
 *
 * This file provides small calculation utilities used throughout the project,
 * including absolute value, Newton's method square root, arithmetic mean,
 * sample standard deviation, sample Pearson Correlation Coefficient,
 * and wind-speed unit conversion.
 *
 * @author Heng Kiao Woon
 * @version 03
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial creation for Assignment 1.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 * 03 03/04/2026 Heng Kiao Woon - Refactored statistical functions to use Vector.
 */

#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include "Vector.h"

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
 * @brief Calculates the arithmetic mean of a numeric vector.
 * @param dataVector Vector of float values.
 * @return Mean value. Returns 0 if the vector is empty.
 */
float calculateMean(const Vector<float>& dataVector);

/**
 * @brief Calculates the sample standard deviation of a numeric vector.
 * @param dataVector Vector of float values.
 * @return Sample standard deviation. Returns 0 if the vector has fewer than 2 elements.
 */
float calculateStandardDeviation(const Vector<float>& dataVector);

/**
 * @brief Calculates the sample Pearson Correlation Coefficient between two numeric vectors.
 * @param x First vector.
 * @param y Second vector.
 * @return Pearson correlation coefficient. Returns 0 if invalid.
 *
 * Both vectors must have the same size and contain at least 2 elements.
 */
float sPCC(const Vector<float>& x, const Vector<float>& y);

/**
 * @brief Converts speed from meters per second to kilometers per hour.
 * @param ms Speed in m/s.
 * @return Speed in km/h (ms * 3.6).
 */
float ConvertMsToKmh(float ms);

#endif // CALCULATOR_H_INCLUDED
