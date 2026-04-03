/**
 * @file WeatherFileReader.h
 * @brief Reads weather CSV files and populates a WeatherLogType.
 *
 * This class handles ONLY file reading + parsing (SRP).
 * WeatherLogType handles storage + calculations.
 *
 *
 * @author Heng Kiao Woon
 * @version 02
 * @date 01/03/2026
 */

#ifndef WEATHERFILEREADER_H_INCLUDED
#define WEATHERFILEREADER_H_INCLUDED

#include <string>
#include "WeatherLogType.h"

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
    /**
     * @brief Loads weather data using a config file that lists CSV filenames (one per line).
     *
     * Supports filenames like:
     * - "data/MetData-31-3.csv"
     * - "MetData-31-3.csv" (auto-tries data/ prefix)
     *
     * @param log WeatherLogType to populate.
     * @param configPath Config file path (default: "data/data_source.txt").
     */
    void LoadFromConfig(WeatherLogType& log, const std::string& configPath = "data/data_source.txt");
};

#endif // WEATHERFILEREADER_H_INCLUDED
