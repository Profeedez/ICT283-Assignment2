/**
 * @file WeatherFileReader.h
 * @brief Declares the WeatherFileReader class for loading weather data from files.
 *
 * WeatherFileReader is responsible for reading configured CSV input files,
 * extracting the required weather columns, converting raw text into program
 * values, and storing the results in the weather data model.
 *
 * Assignment 2:
 * Data is loaded directly into WeatherBstMapStore rather than WeatherLogType.
 *
 * @author Heng Kiao Woon
 * @version 04
 * @date 04/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial weather file reader declaration.
 * 02 01/03/2026 Heng Kiao Woon - Expanded description and data-loading behaviour.
 * 03 03/04/2026 Heng Kiao Woon - Updated file header, removed WeatherLogType.
 * 04 04/04/2026 Heng Kiao Woon - Added API using WeatherBstMapStore.
 */

#ifndef WEATHERFILEREADER_H_INCLUDED
#define WEATHERFILEREADER_H_INCLUDED

#include <string>
#include "WeatherBstMapStore.h"

/**
 * @class WeatherFileReader
 * @brief Reads weather data from configured CSV files into the BST-based store.
 */
class WeatherFileReader
{
public:
    /**
     * @brief Loads all CSV files listed in the configuration file.
     * @param configPath Path to the configuration file.
     * @param store Weather BST/map store that receives loaded records.
     */
    void LoadFromConfig(const std::string& configPath, WeatherBstMapStore& store) const;

    /**
     * @brief Loads all CSV files listed in the default configuration file.
     * @param store Weather BST/map store that receives loaded records.
     */
    void LoadFromConfig(WeatherBstMapStore& store) const;
};

#endif // WEATHERFILEREADER_H_INCLUDED
