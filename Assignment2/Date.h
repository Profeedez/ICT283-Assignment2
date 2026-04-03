/**
 * @file Date.h
 * @brief Declares the Date class and related stream/comparison operators.
 *
 * The Date class represents a Gregorian calendar date using day, month, and
 * year fields. It provides simple validation logic, leap-year handling, and
 * operator support needed by the weather record classes.
 *
 * @author Heng Kiao Woon
 * @version 03
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial Date class declaration.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 * 03 03/04/2026 Heng Kiao Woon - Added comparison operators for BST ordering.
 */

#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>

using std::ostream;
using std::istream;

/**
 * @class Date
 * @brief Represents a calendar date (day, month, year) with validation.
 *
 * Validation includes:
 * - month range: 1..12
 * - day range based on month length and leap year rules
 *
 * @bug Does not handle dates before the Gregorian calendar transition.
 */
class Date
{
public:
    /**
     * @brief Constructs a date with default/zero values.
     * @note The default values depend on your .cpp (often 0/0/0).
     */
    Date();

    /**
     * @brief Constructs a date from day, month, and year (validated).
     * @param day Day of month.
     * @param month Month of year (1-12).
     * @param year Year value.
     * @note Invalid values are typically corrected to 0 (check your .cpp).
     */
    Date(int day, int month, int year);

    /**
     * @brief Gets the day value.
     * @return Day of month.
     */
    int GetDay() const;

    /**
     * @brief Sets the day value (validated against current month/year).
     * @param day New day value.
     */
    void SetDay(int day);

    /**
     * @brief Gets the month value.
     * @return Month of year (1-12).
     */
    int GetMonth() const;

    /**
     * @brief Sets the month value (may re-validate the current day).
     * @param month New month value.
     */
    void SetMonth(int month);

    /**
     * @brief Gets the year value.
     * @return Year value.
     */
    int GetYear() const;

    /**
     * @brief Sets the year value (may re-validate the current day for leap years).
     * @param year New year value.
     */
    void SetYear(int year);

private:
    int m_day;      ///< Day (typically 1-31; may be 0 if invalid).
    int m_month;    ///< Month (1-12; may be 0 if invalid).
    int m_year;     ///< Year.

    /**
     * @brief Determines whether a given year is a leap year.
     * @param year Year to test.
     * @return true if @p year is a leap year; otherwise false.
     */
    bool IsLeapYear(int year) const;

    /**
     * @brief Validates a day value for a given month/year.
     * @param day Day to validate.
     * @param month Month to validate against.
     * @param year Year to validate against (for leap years).
     * @return A corrected day value (commonly returns 0 when invalid).
     */
    int ValidateDay(int day, int month, int year) const;
};

/**
 * @brief Extracts a Date from an input stream.
 * @param input Input stream.
 * @param date  Date object to receive parsed values.
 * @return The same input stream (for chaining).
 */
istream& operator>>(istream& input, Date& date);

/**
 * @brief Inserts a Date into an output stream.
 * @param os   Output stream.
 * @param date Date to print.
 * @return The same output stream (for chaining).
 */
ostream& operator<<(ostream& os, const Date& date);

/**
 * @brief Equality comparison between two Date objects.
 * @param left Left-hand Date.
 * @param right Right-hand Date.
 * @return true if both dates are equal, otherwise false.
 */
bool operator==(const Date& left, const Date& right);

/**
 * @brief Inequality comparison between two Date objects.
 * @param left Left-hand Date.
 * @param right Right-hand Date.
 * @return true if the dates are not equal, otherwise false.
 */
bool operator!=(const Date& left, const Date& right);

/**
 * @brief Less-than comparison between two Date objects.
 * @param left Left-hand Date.
 * @param right Right-hand Date.
 * @return true if @p left is earlier than @p right, otherwise false.
 */
bool operator<(const Date& left, const Date& right);

/**
 * @brief Greater-than comparison between two Date objects.
 * @param left Left-hand Date.
 * @param right Right-hand Date.
 * @return true if @p left is later than @p right, otherwise false.
 */
bool operator>(const Date& left, const Date& right);

/**
 * @brief Less-than-or-equal comparison between two Date objects.
 * @param left Left-hand Date.
 * @param right Right-hand Date.
 * @return true if @p left is earlier than or equal to @p right.
 */
bool operator<=(const Date& left, const Date& right);

/**
 * @brief Greater-than-or-equal comparison between two Date objects.
 * @param left Left-hand Date.
 * @param right Right-hand Date.
 * @return true if @p left is later than or equal to @p right.
 */
bool operator>=(const Date& left, const Date& right);

#endif // DATE_H_INCLUDED
