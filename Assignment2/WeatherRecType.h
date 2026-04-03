/**
 * @file WeatherRecType.h
 * @brief Declares the WeatherRecType class for a single weather observation.
 *
 * A WeatherRecType stores the timestamp of an observation together with the
 * measured wind speed, ambient temperature, and solar radiation values used by
 * the program.
 *
 * @author Heng Kiao Woon
 * @version 02
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial WeatherRecType declaration.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 */

#ifndef WEATHERRECTYPE_H_INCLUDED
#define WEATHERRECTYPE_H_INCLUDED

#include "Date.h"
#include "Time.h"

/**
 * @class WeatherRecType
 * @brief Represents one weather observation (date/time + measured values).
 *
 * This class is a small data container used by WeatherLogType.
 * Comparison (operator==) is intended for duplicate detection (same timestamp).
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
     * @param ambientTemperature Ambient temperature in degrees Celsius ( C).
     * @param solarRadiation Solar radiation in watts per square meter (W/m^2).
     */
    WeatherRecType(const Date& date, const Time& time,
                   float speed, float ambientTemperature, float solarRadiation);

    /**
     * @name Getters
     * @{
     */

    /**
     * @brief Gets the observation date.
     * @return The Date stored in this record.
     */
    Date  GetDate() const;

    /**
     * @brief Gets the observation time.
     * @return The Time stored in this record.
     */
    Time  GetTime() const;

    /**
     * @brief Gets the wind speed.
     * @return Wind speed in m/s.
     */
    float GetSpeed() const;

    /**
     * @brief Gets the ambient temperature.
     * @return Ambient temperature in  C.
     */
    float GetAmbientTemperature() const;

    /**
     * @brief Gets the solar radiation.
     * @return Solar radiation in W/m^2.
     */
    float GetSolarRadiation() const;

    /**
     * @brief Compatibility alias for ambient temperature.
     * @return Ambient temperature in  C.
     * @note Provided for older code that expects GetTemperature().
     */
    float GetTemperature() const
    {
        return GetAmbientTemperature();
    }

    /** @} */

    /**
     * @name Setters
     * @{
     */

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
     * @param ambientTemperature New temperature value in  C.
     */
    void SetAmbientTemperature(float ambientTemperature);

    /**
     * @brief Sets the solar radiation.
     * @param solarRadiation New solar radiation value in W/m^2.
     */
    void SetSolarRadiation(float solarRadiation);

    /**
     * @brief Compatibility alias for ambient temperature setter.
     * @param t New temperature value in  C.
     * @note Provided for older code that expects SetTemperature().
     */
    void SetTemperature(float t)
    {
        SetAmbientTemperature(t);
    }

    /** @} */

    /**
     * @brief Compares two records for equality.
     * @param other Record to compare with.
     * @return true if both records refer to the same timestamp (and therefore are duplicates);
     *         otherwise false.
     * @note Typical duplicate detection compares date + time only. If your .cpp compares
     *       additional fields, this documentation still remains correct for its intended use.
     */
    bool operator==(const WeatherRecType& other) const;

private:
    Date  m_date;               /// Observation date.
    Time  m_time;               /// Observation time.
    float m_speed;              /// Wind speed (m/s).
    float m_ambientTemperature; /// Ambient temperature ( C).
    float m_solarRadiation;     /// Solar radiation (W/m^2).
};

#endif // WEATHERRECTYPE_H_INCLUDED
