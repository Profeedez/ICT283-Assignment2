// Time.cpp
//
// Implementation of the Time class and related operators.
// Provides validation, setters, getters, and stream/comparison support for time values.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial Time class implementation.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes

#include "Time.h"

//----------------------------------------------------------------------------
// Function implementations

//----------------------------------------------------------------------------
// Default constructor. Initialises to 00:00:00.
Time::Time()
    : m_hour(0), m_minute(0), m_second(0)
{
}

//----------------------------------------------------------------------------
// Constructs a time and validates each component.
Time::Time(int hour, int minute, int second)
    : m_hour(0), m_minute(0), m_second(0)
{
    SetHour(hour);
    SetMinute(minute);
    SetSecond(second);
}

// ---------------- Getters ----------------

//----------------------------------------------------------------------------
// Gets the hour component (0-23).
int Time::GetHour() const
{
    return m_hour;
}
//----------------------------------------------------------------------------
// Gets the minute component (0-59).
int Time::GetMinute() const
{
    return m_minute;
}
//----------------------------------------------------------------------------
// Gets the second component (0-59).
int Time::GetSecond() const
{
    return m_second;
}

// ---------------- Setters ----------------

//----------------------------------------------------------------------------
// Sets the hour component; invalid values become 0.
void Time::SetHour(int hour)
{
    m_hour = (hour >= 0 && hour <= 23) ? hour : 0;
}

//----------------------------------------------------------------------------
// Sets the minute component; invalid values become 0.
void Time::SetMinute(int minute)
{
    m_minute = (minute >= 0 && minute <= 59) ? minute : 0;
}

//----------------------------------------------------------------------------
// Sets the second component; invalid values become 0.
void Time::SetSecond(int second)
{
    m_second = (second >= 0 && second <= 59) ? second : 0;
}

// ---------------- Stream Input ----------------
// Accepts formats:
// HH:MM
// HH:MM:SS
//----------------------------------------------------------------------------
// Stream input for HH:MM or HH:MM:SS formats.
istream& operator>>(istream& input, Time& time)
{
    int hour = 0, minute = 0, second = 0;
    char colon1 = 0, colon2 = 0;

    input >> hour >> colon1 >> minute;

    if (input.peek() == ':')
    {
        input >> colon2 >> second;
    }

    time.SetHour(hour);
    time.SetMinute(minute);
    time.SetSecond(second);

    return input;
}

// ---------------- Stream Output ----------------

//----------------------------------------------------------------------------
// Stream output in H:M:S format.
ostream& operator<<(ostream& os, const Time& time)
{
    os << time.GetHour() << ":"
       << time.GetMinute() << ":"
       << time.GetSecond();
    return os;
}
