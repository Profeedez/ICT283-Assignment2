/**
 * @file WeatherBstMapStore.h
 * @brief Stores weather records using a BST of years and a map of monthly buckets.
 *
 * This class is the Assignment 2 weather store.
 *
 * The overall structure is:
 *
 * Bst<YearNode>
 *
 * where each YearNode contains:
 *
 *  int year
 *  std::map<int, MonthBucket> recordsByMonth
 *
 * and each MonthBucket contains:
 *
 *  std::map<int, Vector<WeatherRecType> > recordsByDay
 *
 * This means:
 * - the outer BST groups data by year
 * - the inner map groups data by month
 * - each month groups records by day
 * - each day stores weather records in a Vector ordered by file input sequence
 *
 * This optimized design avoids inserting chronologically sorted weather data
 * into an unbalanced monthly BST, which previously caused poor loading
 * performance for large files.
 *
 * @author Heng Kiao Woon
 * @version 07
 * @date 04/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial map/BST store implementation.
 * 02 04/04/2026 Heng Kiao Woon - Removed WeatherLogType and refactored for Assignment 2.
 * 03 04/04/2026 Heng Kiao Woon - Updated documentation and aligned with WeatherRecType design.
 * 04 04/04/2026 Heng Kiao Woon - Redesigned store to use Bst<YearNode> with monthly BST map.
 * 05 04/04/2026 Heng Kiao Woon - Added MAD calculations for option 4.
 * 06 04/04/2026 Heng Kiao Woon - Identified loading slowdown caused by skewed monthly BST insertion.
 * 07 04/04/2026 Heng Kiao Woon - Optimized monthly storage using MonthBucket with day grouping and cached statistics.
 */

#ifndef WEATHERBSTMAPSTORE_H_INCLUDED
#define WEATHERBSTMAPSTORE_H_INCLUDED

#include <map>
#include <string>
#include "Bst.h"
#include "WeatherRecType.h"
#include "Vector.h"

/**
 * @struct MonthBucket
 * @brief Stores all weather records and cached statistics for one month.
 *
 * Each MonthBucket stores:
 * - a map from day number to a Vector of WeatherRecType records
 * - cached wind speed values for MAD calculation
 * - cached temperature values for MAD calculation
 * - running totals and counts for mean and standard deviation
 * - accumulated solar radiation total
 *
 * This structure improves loading performance because appending to a Vector
 * is much faster than repeatedly inserting sorted data into an unbalanced BST.
 */
struct MonthBucket
{
    /**
     * @brief Default constructor.
     */
    MonthBucket();

    /**
     * @brief Map of day to weather records for that day.
     */
    std::map<int, Vector<WeatherRecType> > recordsByDay;

    /**
     * @brief Cached valid wind speed values for MAD calculation.
     */
    Vector<float> windValues;

    /**
     * @brief Cached valid temperature values for MAD calculation.
     */
    Vector<float> temperatureValues;

    /**
     * @brief Number of valid wind speed values.
     */
    int validWindCount;

    /**
     * @brief Sum of valid wind speed values.
     */
    float windSum;

    /**
     * @brief Sum of squares of valid wind speed values.
     */
    float windSumSquares;

    /**
     * @brief Number of valid ambient temperature values.
     */
    int validTemperatureCount;

    /**
     * @brief Sum of valid ambient temperature values.
     */
    float temperatureSum;

    /**
     * @brief Sum of squares of valid ambient temperature values.
     */
    float temperatureSumSquares;

    /**
     * @brief True if at least one valid solar radiation value exists.
     */
    bool hasValidSolar;

    /**
     * @brief Total solar radiation for the month.
     */
    float totalSolar;
};

/**
 * @struct YearNode
 * @brief Represents one year in the outer BST.
 *
 * Each YearNode stores:
 * - the year key used for BST ordering
 * - a map from month number to a MonthBucket for that month
 *
 * The BST ordering of YearNode depends only on the year field.
 */
struct YearNode
{
    /**
     * @brief Default constructor.
     */
    YearNode();

    /**
     * @brief Constructs a YearNode with a given year.
     * @param y The year value.
     */
    explicit YearNode(int y);

    /**
     * @brief Year key for BST ordering.
     */
    int year;

    /**
     * @brief Map of month to MonthBucket of weather records.
     *
     * Month keys are 1 to 12.
     */
    mutable std::map<int, MonthBucket> recordsByMonth;
};

/**
 * @brief Equality comparison for YearNode.
 * @param left Left-hand node.
 * @param right Right-hand node.
 * @return True if the years are equal.
 */
bool operator==(const YearNode& left, const YearNode& right);

/**
 * @brief Inequality comparison for YearNode.
 * @param left Left-hand node.
 * @param right Right-hand node.
 * @return True if the years are different.
 */
bool operator!=(const YearNode& left, const YearNode& right);

/**
 * @brief Less-than comparison for YearNode.
 * @param left Left-hand node.
 * @param right Right-hand node.
 * @return True if left year is less than right year.
 */
bool operator<(const YearNode& left, const YearNode& right);

/**
 * @brief Greater-than comparison for YearNode.
 * @param left Left-hand node.
 * @param right Right-hand node.
 * @return True if left year is greater than right year.
 */
bool operator>(const YearNode& left, const YearNode& right);

/**
 * @brief Less-than-or-equal comparison for YearNode.
 * @param left Left-hand node.
 * @param right Right-hand node.
 * @return True if left year is less than or equal to right year.
 */
bool operator<=(const YearNode& left, const YearNode& right);

/**
 * @brief Greater-than-or-equal comparison for YearNode.
 * @param left Left-hand node.
 * @param right Right-hand node.
 * @return True if left year is greater than or equal to right year.
 */
bool operator>=(const YearNode& left, const YearNode& right);

/**
 * @class WeatherBstMapStore
 * @brief Stores and processes weather records using a BST of YearNode objects.
 *
 * This class supports:
 * - insertion of records into the correct year, month, and day structure
 * - record lookup
 * - monthly mean, standard deviation, and mean absolute deviation calculations
 * - monthly solar radiation totals
 * - monthly validity checks
 * - Pearson correlation calculations across all years for a selected month
 * - yearly CSV export
 */
class WeatherBstMapStore
{
public:
    /**
     * @brief Constructs an empty weather store.
     */
    WeatherBstMapStore();

    /**
     * @brief Inserts a record into the correct year, month, and day structure.
     *
     * The year is used to locate or create a YearNode in the outer BST.
     * The month is then used to locate or create a MonthBucket inside that year.
     * The day is then used to locate or create a Vector of WeatherRecType records.
     *
     * Cached statistics are updated immediately after successful insertion.
     *
     * @param record The weather record to insert.
     * @return True if inserted successfully, false if it is a duplicate.
     */
    bool AddRecord(const WeatherRecType& record);

    /**
     * @brief Checks whether the given year exists in the store.
     * @param year The year to search for.
     * @return True if the year exists, otherwise false.
     */
    bool HasYear(int year) const;

    /**
     * @brief Returns the number of year nodes stored.
     * @return Number of unique years in the outer BST.
     */
    int GetYearCount() const;

    /**
     * @brief Checks whether a specific record exists in the store.
     * @param year The year to search in.
     * @param record The record to search for.
     * @return True if the record exists, otherwise false.
     */
    bool ContainsRecord(int year, const WeatherRecType& record) const;

    /**
     * @brief Calculates the mean wind speed for a month in a year.
     * @param month The month to process (1-12).
     * @param year The year to process.
     * @return Mean wind speed, or 0.0f if no valid data exists.
     */
    float FindSpeedMean(int month, int year) const;

    /**
     * @brief Calculates sample standard deviation of wind speed for a month in a year.
     * @param month The month to process (1-12).
     * @param year The year to process.
     * @return Sample standard deviation, or 0.0f if insufficient valid data exists.
     */
    float FindSpeedStandardDeviation(int month, int year) const;

    /**
     * @brief Calculates mean absolute deviation of wind speed for a month in a year.
     * @param month The month to process (1-12).
     * @param year The year to process.
     * @return MAD, or 0.0f if no valid data exists.
     */
    float FindSpeedMad(int month, int year) const;

    /**
     * @brief Calculates the mean ambient temperature for a month in a year.
     * @param month The month to process (1-12).
     * @param year The year to process.
     * @return Mean temperature, or 0.0f if no valid data exists.
     */
    float FindTemperatureMean(int month, int year) const;

    /**
     * @brief Calculates sample standard deviation of ambient temperature for a month in a year.
     * @param month The month to process (1-12).
     * @param year The year to process.
     * @return Sample standard deviation, or 0.0f if insufficient valid data exists.
     */
    float FindTemperatureStandardDeviation(int month, int year) const;

    /**
     * @brief Calculates mean absolute deviation of ambient temperature for a month in a year.
     * @param month The month to process (1-12).
     * @param year The year to process.
     * @return MAD, or 0.0f if no valid data exists.
     */
    float FindTemperatureMad(int month, int year) const;

    /**
     * @brief Calculates the total solar radiation for a month in a year.
     * @param month The month to process (1-12).
     * @param year The year to process.
     * @return Total solar radiation, or 0.0f if no valid data exists.
     */
    float FindTotalSolar(int month, int year) const;

    /**
     * @brief Checks whether valid wind data exists for a month in a year.
     * @param month The month to check (1-12).
     * @param year The year to check.
     * @return True if at least one valid wind value exists.
     */
    bool HasValidWind(int month, int year) const;

    /**
     * @brief Checks whether valid temperature data exists for a month in a year.
     * @param month The month to check (1-12).
     * @param year The year to check.
     * @return True if at least one valid temperature value exists.
     */
    bool HasValidTemperature(int month, int year) const;

    /**
     * @brief Checks whether valid solar radiation data exists for a month in a year.
     * @param month The month to check (1-12).
     * @param year The year to check.
     * @return True if at least one valid solar value exists.
     */
    bool HasValidSolar(int month, int year) const;

    /**
     * @brief Calculates sample Pearson correlation coefficients for a selected month across all years.
     * @param month The selected month (1-12).
     * @param st Output for speed vs temperature.
     * @param sr Output for speed vs solar radiation.
     * @param tr Output for temperature vs solar radiation.
     */
    void FindSPCCForMonthAllYears(int month, float& st, float& sr, float& tr) const;

    /**
     * @brief Exports yearly summary statistics to a CSV file.
     * @param year The year to export.
     * @param outputFile Path of the output CSV file.
     */
    void ExportSummaryCSV(int year, const std::string& outputFile) const;

private:
    /**
     * @brief BST storing YearNode objects.
     */
    Bst<YearNode> m_yearTree;

    /**
     * @brief Number of unique years stored in the BST.
     */
    int m_yearCount;
};

#endif // WEATHERBSTMAPSTORE_H_INCLUDED
