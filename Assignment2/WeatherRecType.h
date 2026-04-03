/**
 * @file WeatherRecType.h
 * @brief Declares the WeatherRecType class for a single weather observation.
 *
 * A WeatherRecType stores the timestamp of an observation together with the
 * measured wind speed, ambient temperature, and solar radiation values used by
 * the program.
 *
 * @author Heng Kiao Woon
 * @version 03
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial WeatherRecType declaration.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 * 03 03/04/2026 Heng Kiao Woon - Added comparison operators for BST ordering.
 */

#ifndef WEATHERRECTYPE_H_INCLUDED
#define WEATHERRECTYPE_H_INCLUDED

#include "Date.h"
#include "Time.h"

/**
 * @class WeatherRecType
 * @brief Represents one weather observation (date/time + measured values).
 *
 * This class is a small data container used by the weather storage classes.
 * Ordering and equality are based on timestamp so that records can be stored
 * and searched correctly inside a binary search tree.
 */
class WeatherRecType
{
public:
    /**
     * @brief Constructs a record with default/zero values.
     */
    WeatherRecType();

    /**
     * @brief Constructs a record with all fields set.
     * @param date The observation date.
     * @param time The observation time.
     * @param speed Wind speed in meters per second (m/s).
     * @param ambientTemperature Ambient temperature in degrees Celsius.
     * @param solarRadiation Solar radiation in watts per square meter (W/m^2).
     */
    WeatherRecType(const Date& date, const Time& time,
                   float speed, float ambientTemperature, float solarRadiation);

    /**
     * @brief Gets the observation date.
     * @return The Date stored in this record.
     */
    Date GetDate() const;

    /**
     * @brief Gets the observation time.
     * @return The Time stored in this record.
     */
    Time GetTime() const;

    /**
     * @brief Gets the wind speed.
     * @return Wind speed in m/s.
     */
    float GetSpeed() const;

    /**
     * @brief Gets the ambient temperature.
     * @return Ambient temperature in degrees Celsius.
     */
    float GetAmbientTemperature() const;

    /**
     * @brief Gets the solar radiation.
     * @return Solar radiation in W/m^2.
     */
    float GetSolarRadiation() const;

    /**
     * @brief Compatibility alias for ambient temperature.
     * @return Ambient temperature in degrees Celsius.
     */
    float GetTemperature() const
    {
        return GetAmbientTemperature();
    }

    /**
     * @brief Sets the observation date.
     * @param date New Date value.
     */
    void SetDate(const Date& date);

    /**
     * @brief Sets the observation time.
     * @param time New Time value.
     */
    void SetTime(const Time& time);

    /**
     * @brief Sets the wind speed.
     * @param speed New speed value in m/s.
     */
    void SetSpeed(float speed);

    /**
     * @brief Sets the ambient temperature.
     * @param ambientTemperature New temperature value in degrees Celsius.
     */
    void SetAmbientTemperature(float ambientTemperature);

    /**
     * @brief Sets the solar radiation.
     * @param solarRadiation New solar radiation value in W/m^2.
     */
    void SetSolarRadiation(float solarRadiation);

    /**
     * @brief Compatibility alias for ambient temperature setter.
     * @param t New temperature value in degrees Celsius.
     */
    void SetTemperature(float t)
    {
        SetAmbientTemperature(t);
    }

private:
    Date  m_date;
    Time  m_time;
    float m_speed;
    float m_ambientTemperature;
    float m_solarRadiation;
};

/**
 * @brief Equality comparison between two weather records.
 * @param left Left-hand record.
 * @param right Right-hand record.
 * @return true if both records have the same timestamp, otherwise false.
 */
bool operator==(const WeatherRecType& left, const WeatherRecType& right);

/**
 * @brief Inequality comparison between two weather records.
 * @param left Left-hand record.
 * @param right Right-hand record.
 * @return true if the records do not have the same timestamp, otherwise false.
 */
bool operator!=(const WeatherRecType& left, const WeatherRecType& right);

/**
 * @brief Less-than comparison between two weather records.
 * @param left Left-hand record.
 * @param right Right-hand record.
 * @return true if @p left is earlier than @p right, otherwise false.
 */
bool operator<(const WeatherRecType& left, const WeatherRecType& right);

/**
 * @brief Greater-than comparison between two weather records.
 * @param left Left-hand record.
 * @param right Right-hand record.
 * @return true if @p left is later than @p right, otherwise false.
 */
bool operator>(const WeatherRecType& left, const WeatherRecType& right);

/**
 * @brief Less-than-or-equal comparison between two weather records.
 * @param left Left-hand record.
 * @param right Right-hand record.
 * @return true if @p left is earlier than or equal to @p right.
 */
bool operator<=(const WeatherRecType& left, const WeatherRecType& right);

/**
 * @brief Greater-than-or-equal comparison between two weather records.
 * @param left Left-hand record.
 * @param right Right-hand record.
 * @return true if @p left is later than or equal to @p right.
 */
bool operator>=(const WeatherRecType& left, const WeatherRecType& right);

#endif // WEATHERRECTYPE_H_INCLUDED
