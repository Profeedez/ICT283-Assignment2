// WeatherRecType.cpp
//
// Implementation of the WeatherRecType class and related operators.
// Stores a single weather observation with date, time, wind speed,
// temperature, and solar radiation.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial WeatherRecType implementation.
// 02 01/03/2026 Heng Kiao Woon - Added comparison operator support.
// 03 03/04/2026 Heng Kiao Woon - Updated file header.
// 04 03/04/2026 Heng Kiao Woon - Added full ordering operators for BST use.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "WeatherRecType.h"

//----------------------------------------------------------------------------
// Constructors
WeatherRecType::WeatherRecType()
    : m_date(), m_time(), m_speed(0.0f), m_ambientTemperature(0.0f), m_solarRadiation(0.0f)
{
}

WeatherRecType::WeatherRecType(const Date& date, const Time& time,
                               float speed, float ambientTemperature, float solarRadiation)
    : m_date(date),
      m_time(time),
      m_speed(speed),
      m_ambientTemperature(ambientTemperature),
      m_solarRadiation(solarRadiation)
{
}

//----------------------------------------------------------------------------
// Accessor methods
Date WeatherRecType::GetDate() const
{
    return m_date;
}

Time WeatherRecType::GetTime() const
{
    return m_time;
}

float WeatherRecType::GetSpeed() const
{
    return m_speed;
}

float WeatherRecType::GetAmbientTemperature() const
{
    return m_ambientTemperature;
}

float WeatherRecType::GetSolarRadiation() const
{
    return m_solarRadiation;
}

//----------------------------------------------------------------------------
// Setter methods
void WeatherRecType::SetDate(const Date& date)
{
    m_date = date;
}

void WeatherRecType::SetTime(const Time& time)
{
    m_time = time;
}

void WeatherRecType::SetSpeed(float speed)
{
    m_speed = speed;
}

void WeatherRecType::SetAmbientTemperature(float ambientTemperature)
{
    m_ambientTemperature = ambientTemperature;
}

void WeatherRecType::SetSolarRadiation(float solarRadiation)
{
    m_solarRadiation = solarRadiation;
}

//----------------------------------------------------------------------------
// Comparison operators for WeatherRecType ordering.
// Ordering is based on timestamp only: date first, then time.

bool operator==(const WeatherRecType& left, const WeatherRecType& right)
{
    return left.GetDate() == right.GetDate()
        && left.GetTime() == right.GetTime();
}

bool operator!=(const WeatherRecType& left, const WeatherRecType& right)
{
    return !(left == right);
}

bool operator<(const WeatherRecType& left, const WeatherRecType& right)
{
    if (left.GetDate() != right.GetDate())
    {
        return left.GetDate() < right.GetDate();
    }

    return left.GetTime() < right.GetTime();
}

bool operator>(const WeatherRecType& left, const WeatherRecType& right)
{
    return right < left;
}

bool operator<=(const WeatherRecType& left, const WeatherRecType& right)
{
    return !(right < left);
}

bool operator>=(const WeatherRecType& left, const WeatherRecType& right)
{
    return !(left < right);
}
