/**
 * @file Time.h
 * @brief Declares the Time class and related stream/comparison operators.
 *
 * The Time class represents a time of day using hour, minute, and second
 * fields. It provides validation and basic operator support required by the
 * weather record classes.
 *
 * @author Heng Kiao Woon
 * @version 03
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial Time class declaration.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 * 03 03/04/2026 Heng Kiao Woon - Added comparison operators for BST ordering.
 */

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <iostream>

using std::istream;
using std::ostream;

/**
 * @class Time
 * @brief Represents a time of day (hour, minute, second).
 */
class Time
{
public:
    /**
     * @brief Constructs a time with default values.
     * @note Default values depend on your .cpp (commonly 0:0:0).
     */
    Time();

    /**
     * @brief Constructs a time from hour, minute, and optional second.
     * @param hour Hour value (0-23).
     * @param minute Minute value (0-59).
     * @param second Second value (0-59). Defaults to 0.
     */
    Time(int hour, int minute, int second = 0);

    /**
     * @brief Gets the hour component.
     * @return Hour (0-23).
     */
    int GetHour() const;

    /**
     * @brief Sets the hour component.
     * @param hour New hour value (0-23).
     */
    void SetHour(int hour);

    /**
     * @brief Gets the minute component.
     * @return Minute (0-59).
     */
    int GetMinute() const;

    /**
     * @brief Sets the minute component.
     * @param minute New minute value (0-59).
     */
    void SetMinute(int minute);

    /**
     * @brief Gets the second component.
     * @return Second (0-59).
     */
    int GetSecond() const;

    /**
     * @brief Sets the second component.
     * @param second New second value (0-59).
     */
    void SetSecond(int second);

private:
    int m_hour;    ///< Hour (0-23).
    int m_minute;  ///< Minute (0-59).
    int m_second;  ///< Second (0-59).
};

/**
 * @brief Extracts a Time from an input stream.
 * @param input Input stream.
 * @param time  Time object to receive parsed values.
 * @return The same input stream (for chaining).
 */
istream& operator>>(istream& input, Time& time);

/**
 * @brief Inserts a Time into an output stream.
 * @param os   Output stream.
 * @param time Time to print.
 * @return The same output stream (for chaining).
 */
ostream& operator<<(ostream& os, const Time& time);

/**
 * @brief Equality comparison between two Time objects.
 * @param left Left-hand Time.
 * @param right Right-hand Time.
 * @return true if both times are equal, otherwise false.
 */
bool operator==(const Time& left, const Time& right);

/**
 * @brief Inequality comparison between two Time objects.
 * @param left Left-hand Time.
 * @param right Right-hand Time.
 * @return true if the times are not equal, otherwise false.
 */
bool operator!=(const Time& left, const Time& right);

/**
 * @brief Less-than comparison between two Time objects.
 * @param left Left-hand Time.
 * @param right Right-hand Time.
 * @return true if @p left is earlier than @p right, otherwise false.
 */
bool operator<(const Time& left, const Time& right);

/**
 * @brief Greater-than comparison between two Time objects.
 * @param left Left-hand Time.
 * @param right Right-hand Time.
 * @return true if @p left is later than @p right, otherwise false.
 */
bool operator>(const Time& left, const Time& right);

/**
 * @brief Less-than-or-equal comparison between two Time objects.
 * @param left Left-hand Time.
 * @param right Right-hand Time.
 * @return true if @p left is earlier than or equal to @p right.
 */
bool operator<=(const Time& left, const Time& right);

/**
 * @brief Greater-than-or-equal comparison between two Time objects.
 * @param left Left-hand Time.
 * @param right Right-hand Time.
 * @return true if @p left is later than or equal to @p right.
 */
bool operator>=(const Time& left, const Time& right);

#endif // TIME_H_INCLUDED
