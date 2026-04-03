/**
 * @file WeatherFileReader.h
 * @brief Declares the WeatherFileReader class for loading weather data from files.
 *
 * WeatherFileReader is responsible for reading configured CSV input files,
 * extracting the required weather columns, converting raw text into program
 * values, and storing the results in the weather data model.
 *
 * @author Heng Kiao Woon
 * @version 03
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial weather file reader declaration.
 * 02 01/03/2026 Heng Kiao Woon - Expanded description and data-loading behaviour.
 * 03 03/04/2026 Heng Kiao Woon - Updated file header, removed WeatherLogType.
 */

#ifndef WEATHERFILEREADER_H_INCLUDED
#define WEATHERFILEREADER_H_INCLUDED

#include <string>

/**
 * @class WeatherFileReader
 * @brief Reads weather data from a CSV file.
 *
 * The WeatherFileReader class is responsible for reading a
 * weather data file, extracting the required fields such as
 * date, time, wind speed, solar radiation and temperature,
 * and storing them into a WeatherLogType container.
 */

class WeatherFileReader
{
public:

};

#endif // WEATHERFILEREADER_H_INCLUDED
