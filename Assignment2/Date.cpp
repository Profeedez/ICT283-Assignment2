// Date.cpp
//
// Implementation of the Date class.
// Provides basic validation, leap-year logic, and stream operators.
//
// Version
// 01 01/03/2026 Heng Kiao Woon
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Date.h"

//----------------------------------------------------------------------------
// Function implementations

//----------------------------------------------------------------------------
// Default constructor. Initialises to 0/0/0.
Date::Date() : m_day(0), m_month(0), m_year(0)
{

}

//----------------------------------------------------------------------------
// Constructs a date from day/month/year with validation.
Date::Date(int day, int month, int year)
    : m_day(ValidateDay(day, (month >= 1 && month <= 12) ? month : 1, year)),
      m_month((month >= 1 && month <= 12) ? month : 1),
      m_year(year)
{
}



//----------------------------------------------------------------------------
// Gets the day component.
int Date::GetDay() const
{
    return m_day;
}

//----------------------------------------------------------------------------
// Sets the day component (validated for month/year).
void Date::SetDay(int day)
{
    m_day = ValidateDay(day, m_month, m_year);
}

//----------------------------------------------------------------------------
// Gets the month component.
int Date::GetMonth() const
{
    return m_month;
}

//----------------------------------------------------------------------------
// Sets the month component (1-12).
void Date::SetMonth(int month)
{
    if (month >= 1 && month <= 12)
    {
        m_month = month;
    }
}

//----------------------------------------------------------------------------
// Gets the year component.
int Date::GetYear() const
{
    return m_year;
}

//----------------------------------------------------------------------------
// Sets the year component.
void Date::SetYear(int year)
{
    m_year = year;
}

// Getters and Setters omitted for brevity...

//----------------------------------------------------------------------------
// Leap Year Logic - math is divisible by 4 but not 100 unless 400

//----------------------------------------------------------------------------
// Checks whether a year is a leap year.
bool Date::IsLeapYear(int year) const
{
    // A year is a leap year if divisible by 4, unless divisible by 100 but not 400
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//----------------------------------------------------------------------------
// Ensures day falls within month limits

//----------------------------------------------------------------------------
// Validates a day number for a given month/year; returns 0 if invalid.
int Date::ValidateDay(int day, int month, int year) const
{
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Handle Leap Year for February
    if (month == 2 && IsLeapYear(year))
    {
        daysInMonth[2] = 29;
    }

    if (day >= 1 && day <= daysInMonth[month])
    {
        return day;
    }

    // If invalid, return 0 or keep existing (returning 0 here to indicate error)
    return 0;
}

//----------------------------------------------------------------------------
// Stream operations

//----------------------------------------------------------------------------
// Stream output in d/m/y format.
ostream & operator <<(ostream & os, const Date & date)
{
    os << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear();
    return os;
}


//----------------------------------------------------------------------------
// Reads date in dd/mm/yyyy format

//----------------------------------------------------------------------------
// Stream input for dd/mm/yyyy format.
istream & operator >>(istream & input, Date & date)
{
    int day;
    int month;
    int year;
    char slash1, slash2;

    // Reads format: 30/06/2016
    if(input >> day >> slash1 >> month >> slash2 >> year)
    {
        // Set year and month first to ensure day validation works correctly (leap year check)
        date.SetYear(year);
        date.SetMonth(month);
        date.SetDay(day);
    }
    return input;
}
