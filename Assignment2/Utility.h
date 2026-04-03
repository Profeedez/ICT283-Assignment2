/**
 * @file Utility.h
 * @brief Declares shared helper functions used across the project.
 *
 * This file contains general-purpose utility routines for whitespace checks,
 * month-name conversion, trimming, case-insensitive comparisons, CSV header
 * lookup, and validated integer input.
 *
 * @author Heng Kiao Woon
 * @version 04
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial Utility declarations.
 * 02 01/03/2026 Heng Kiao Woon - Expanded parsing and formatting helpers.
 * 03 01/03/2026 Heng Kiao Woon - Added input validation support.
 * 04 03/04/2026 Heng Kiao Woon - Updated file header.
 */

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <string>

/**
 * @brief Checks whether a character is considered whitespace (space, tab, newline, carriage return).
 * @param character Character to test.
 * @return true if @p character is whitespace; otherwise false.
 */
bool IsWhitespaceCharacter(char character);

/**
 * @brief Converts numeric month (1-12) to English month name.
 * @param monthNumber Month number (1-12).
 * @return Month name (e.g., "January"). Returns "Unknown" for invalid month.
 */
std::string ConvertMonth(int monthNumber);

/**
 * @brief Trims leading and trailing whitespace.
 * @param inputText Input string.
 * @return Trimmed copy of @p inputText.
 */
std::string Trim(const std::string& inputText);

/**
 * @brief Case-insensitive equality for ASCII letters.
 * @param firstText First string.
 * @param secondText Second string.
 * @return true if strings are equal ignoring case; otherwise false.
 */
bool EqualsIgnoreCase(const std::string& firstText, const std::string& secondText);

/**
 * @brief Finds the zero-based CSV column index for a given column name in a header line.
 * @param headerLine The header row (one line).
 * @param columnName The column name to locate.
 * @return Zero-based column index, or -1 if not found.
 */
int FindColumnIndex(const std::string& headerLine, const std::string& columnName);

/**
 * @brief Prompts the user until a valid integer is entered.
 * @param promptText Prompt text shown to the user.
 * @param minimumValue Minimum accepted value (inclusive).
 * @param maximumValue Maximum accepted value (inclusive).
 * @return A validated integer in the range [minimumValue, maximumValue].
 */
int GetValidInteger(const std::string& promptText, int minimumValue = 0, int maximumValue = 2147483647);

#endif // UTILITY_H_INCLUDED
