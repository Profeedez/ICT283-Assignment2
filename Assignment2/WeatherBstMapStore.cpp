// WeatherBstMapStore.cpp
//
// Implementation of the WeatherBstMapStore class.
// Stores weather records using an outer BST of years,
// where each year node contains a map of monthly buckets.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial WeatherBstMapStore implementation.
// 02 04/04/2026 Heng Kiao Woon - Added MAD calculations for option 4.
// 03 04/04/2026 Heng Kiao Woon - Optimized monthly storage using MonthBucket and cached statistics.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "WeatherBstMapStore.h"
#include "Calculator.h"
#include "Utility.h"

#include <fstream>
#include <iostream>

//----------------------------------------------------------------------------
// MonthBucket functions
MonthBucket::MonthBucket()
    : recordsByDay(),
      windValues(),
      temperatureValues(),
      validWindCount(0),
      windSum(0.0f),
      windSumSquares(0.0f),
      validTemperatureCount(0),
      temperatureSum(0.0f),
      temperatureSumSquares(0.0f),
      hasValidSolar(false),
      totalSolar(0.0f)
{
}

//----------------------------------------------------------------------------
// YearNode functions
YearNode::YearNode()
    : year(0), recordsByMonth()
{
}

YearNode::YearNode(int y)
    : year(y), recordsByMonth()
{
}

bool operator==(const YearNode& left, const YearNode& right)
{
    return left.year == right.year;
}

bool operator!=(const YearNode& left, const YearNode& right)
{
    return !(left == right);
}

bool operator<(const YearNode& left, const YearNode& right)
{
    return left.year < right.year;
}

bool operator>(const YearNode& left, const YearNode& right)
{
    return right < left;
}

bool operator<=(const YearNode& left, const YearNode& right)
{
    return !(right < left);
}

bool operator>=(const YearNode& left, const YearNode& right)
{
    return !(left < right);
}

//----------------------------------------------------------------------------
// File-local helper state and helper functions
namespace
{
int g_targetYear = 0;
int g_targetMonth = 0;

const YearNode* g_foundYearNode = nullptr;

Vector<float>* g_sForST = nullptr;
Vector<float>* g_tForST = nullptr;
Vector<float>* g_sForSR = nullptr;
Vector<float>* g_rForSR = nullptr;
Vector<float>* g_tForTR = nullptr;
Vector<float>* g_rForTR = nullptr;

//----------------------------------------------------------------------------
// Locates a year node during traversal.
void FindYearNodeByYear(const YearNode& node)
{
    if (node.year == g_targetYear)
    {
        g_foundYearNode = &node;
    }
}

//----------------------------------------------------------------------------
// Finds a year node in the outer BST.
const YearNode* LocateYearNode(const Bst<YearNode>& yearTree, int year)
{
    g_targetYear = year;
    g_foundYearNode = nullptr;

    yearTree.inorderTraversal(FindYearNodeByYear);

    return g_foundYearNode;
}

//----------------------------------------------------------------------------
// Finds a month bucket inside a year node.
const MonthBucket* LocateMonthBucket(const YearNode* yearNode, int month)
{
    if (yearNode == nullptr)
    {
        return nullptr;
    }

    std::map<int, MonthBucket>::const_iterator monthIt =
        yearNode->recordsByMonth.find(month);

    if (monthIt == yearNode->recordsByMonth.end())
    {
        return nullptr;
    }

    return &(monthIt->second);
}

//----------------------------------------------------------------------------
// Checks whether a day vector already contains the same timestamp record.
bool ContainsTimestampInDay(const Vector<WeatherRecType>& dayRecords,
                            const WeatherRecType& record)
{
    for (int i = 0; i < dayRecords.Size(); ++i)
    {
        if (dayRecords[i] == record)
        {
            return true;
        }
    }

    return false;
}

//----------------------------------------------------------------------------
// Computes sample standard deviation from cached sum values.
float ComputeSampleStandardDeviation(float sum, float sumSquares, int count)
{
    if (count < 2)
    {
        return 0.0f;
    }

    const float n = static_cast<float>(count);
    const float mean = sum / n;
    float numerator = sumSquares - (n * mean * mean);

    if (numerator < 0.0f)
    {
        numerator = 0.0f;
    }

    return squareRoot(numerator / static_cast<float>(count - 1));
}

//----------------------------------------------------------------------------
// Collects paired values for sample Pearson correlation coefficient.
void CollectSPCCPairs(const WeatherRecType& record)
{
    const float speed = record.GetSpeed();
    const float temperature = record.GetAmbientTemperature();
    const float solar = record.GetSolarRadiation();

    if (speed >= 0.0f && temperature >= 0.0f &&
        g_sForST != nullptr && g_tForST != nullptr)
    {
        g_sForST->Add(speed);
        g_tForST->Add(temperature);
    }

    if (speed >= 0.0f && solar >= 100.0f &&
        g_sForSR != nullptr && g_rForSR != nullptr)
    {
        g_sForSR->Add(speed);
        g_rForSR->Add(solar);
    }

    if (temperature >= 0.0f && solar >= 100.0f &&
        g_tForTR != nullptr && g_rForTR != nullptr)
    {
        g_tForTR->Add(temperature);
        g_rForTR->Add(solar);
    }
}

//----------------------------------------------------------------------------
// Traverses a year node and collects SPCC pairs from the selected month.
void CollectSPCCFromYearNode(const YearNode& node)
{
    std::map<int, MonthBucket>::const_iterator monthIt =
        node.recordsByMonth.find(g_targetMonth);

    if (monthIt == node.recordsByMonth.end())
    {
        return;
    }

    const MonthBucket& monthBucket = monthIt->second;

    std::map<int, Vector<WeatherRecType> >::const_iterator dayIt =
        monthBucket.recordsByDay.begin();

    while (dayIt != monthBucket.recordsByDay.end())
    {
        const Vector<WeatherRecType>& dayRecords = dayIt->second;

        for (int i = 0; i < dayRecords.Size(); ++i)
        {
            CollectSPCCPairs(dayRecords[i]);
        }

        ++dayIt;
    }
}
}

//----------------------------------------------------------------------------
// Constructors
WeatherBstMapStore::WeatherBstMapStore()
    : m_yearTree(), m_yearCount(0)
{
}

//----------------------------------------------------------------------------
// Core record insertion
bool WeatherBstMapStore::AddRecord(const WeatherRecType& record)
{
    const int year = record.GetDate().GetYear();
    const int month = record.GetDate().GetMonth();
    const int day = record.GetDate().GetDay();

    YearNode searchKey(year);

    if (!m_yearTree.search(searchKey))
    {
        m_yearTree.insert(searchKey);
        ++m_yearCount;
    }

    const YearNode* yearNode = LocateYearNode(m_yearTree, year);

    if (yearNode == nullptr)
    {
        return false;
    }

    MonthBucket& monthBucket = yearNode->recordsByMonth[month];
    Vector<WeatherRecType>& dayRecords = monthBucket.recordsByDay[day];

    if (ContainsTimestampInDay(dayRecords, record))
    {
        return false;
    }

    dayRecords.Add(record);

    const float speed = record.GetSpeed();
    if (speed >= 0.0f)
    {
        monthBucket.windValues.Add(speed);
        monthBucket.windSum += speed;
        monthBucket.windSumSquares += speed * speed;
        ++monthBucket.validWindCount;
    }

    const float temperature = record.GetAmbientTemperature();
    if (temperature >= 0.0f)
    {
        monthBucket.temperatureValues.Add(temperature);
        monthBucket.temperatureSum += temperature;
        monthBucket.temperatureSumSquares += temperature * temperature;
        ++monthBucket.validTemperatureCount;
    }

    const float solar = record.GetSolarRadiation();
    if (solar >= 100.0f)
    {
        monthBucket.hasValidSolar = true;
        monthBucket.totalSolar += (solar * (1.0f / 6.0f)) / 1000.0f;
    }

    return true;
}

//----------------------------------------------------------------------------
// Query methods
bool WeatherBstMapStore::HasYear(int year) const
{
    return m_yearTree.search(YearNode(year));
}

int WeatherBstMapStore::GetYearCount() const
{
    return m_yearCount;
}

bool WeatherBstMapStore::ContainsRecord(int year, const WeatherRecType& record) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, record.GetDate().GetMonth());

    if (monthBucket == nullptr)
    {
        return false;
    }

    std::map<int, Vector<WeatherRecType> >::const_iterator dayIt =
        monthBucket->recordsByDay.find(record.GetDate().GetDay());

    if (dayIt == monthBucket->recordsByDay.end())
    {
        return false;
    }

    return ContainsTimestampInDay(dayIt->second, record);
}

//----------------------------------------------------------------------------
// Wind speed calculations
float WeatherBstMapStore::FindSpeedMean(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    if (monthBucket == nullptr || monthBucket->validWindCount == 0)
    {
        return 0.0f;
    }

    return monthBucket->windSum / static_cast<float>(monthBucket->validWindCount);
}

float WeatherBstMapStore::FindSpeedStandardDeviation(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    if (monthBucket == nullptr)
    {
        return 0.0f;
    }

    return ComputeSampleStandardDeviation(monthBucket->windSum,
                                          monthBucket->windSumSquares,
                                          monthBucket->validWindCount);
}

float WeatherBstMapStore::FindSpeedMad(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    if (monthBucket == nullptr)
    {
        return 0.0f;
    }

    return mad(monthBucket->windValues);
}

//----------------------------------------------------------------------------
// Temperature calculations
float WeatherBstMapStore::FindTemperatureMean(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    if (monthBucket == nullptr || monthBucket->validTemperatureCount == 0)
    {
        return 0.0f;
    }

    return monthBucket->temperatureSum /
           static_cast<float>(monthBucket->validTemperatureCount);
}

float WeatherBstMapStore::FindTemperatureStandardDeviation(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    if (monthBucket == nullptr)
    {
        return 0.0f;
    }

    return ComputeSampleStandardDeviation(monthBucket->temperatureSum,
                                          monthBucket->temperatureSumSquares,
                                          monthBucket->validTemperatureCount);
}

float WeatherBstMapStore::FindTemperatureMad(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    if (monthBucket == nullptr)
    {
        return 0.0f;
    }

    return mad(monthBucket->temperatureValues);
}

//----------------------------------------------------------------------------
// Solar radiation calculations
float WeatherBstMapStore::FindTotalSolar(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    if (monthBucket == nullptr)
    {
        return 0.0f;
    }

    return monthBucket->totalSolar;
}

//----------------------------------------------------------------------------
// Data presence checks
bool WeatherBstMapStore::HasValidWind(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    return monthBucket != nullptr && monthBucket->validWindCount > 0;
}

bool WeatherBstMapStore::HasValidTemperature(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    return monthBucket != nullptr && monthBucket->validTemperatureCount > 0;
}

bool WeatherBstMapStore::HasValidSolar(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const MonthBucket* monthBucket = LocateMonthBucket(yearNode, month);

    return monthBucket != nullptr && monthBucket->hasValidSolar;
}

//----------------------------------------------------------------------------
// Correlation calculations
void WeatherBstMapStore::FindSPCCForMonthAllYears(int month, float& st, float& sr, float& tr) const
{
    Vector<float> sForST;
    Vector<float> tForST;
    Vector<float> sForSR;
    Vector<float> rForSR;
    Vector<float> tForTR;
    Vector<float> rForTR;

    g_targetMonth = month;
    g_sForST = &sForST;
    g_tForST = &tForST;
    g_sForSR = &sForSR;
    g_rForSR = &rForSR;
    g_tForTR = &tForTR;
    g_rForTR = &rForTR;

    m_yearTree.inorderTraversal(CollectSPCCFromYearNode);

    g_sForST = nullptr;
    g_tForST = nullptr;
    g_sForSR = nullptr;
    g_rForSR = nullptr;
    g_tForTR = nullptr;
    g_rForTR = nullptr;

    st = sPCC(sForST, tForST);
    sr = sPCC(sForSR, rForSR);
    tr = sPCC(tForTR, rForTR);
}

//----------------------------------------------------------------------------
// File export
void WeatherBstMapStore::ExportSummaryCSV(int year, const std::string& outputFile) const
{
    std::ofstream out(outputFile.c_str());

    if (!out.is_open())
    {
        std::cout << "Error: Could not open output file.\n";
        return;
    }

    out << year << "\n";

    bool hasAnyData = false;

    for (int month = 1; month <= 12; ++month)
    {
        const bool hasWind = HasValidWind(month, year);
        const bool hasTemp = HasValidTemperature(month, year);
        const bool hasSolar = HasValidSolar(month, year);

        if (!hasWind && !hasTemp && !hasSolar)
        {
            continue;
        }

        hasAnyData = true;

        const float meanSpeed = FindSpeedMean(month, year);
        const float sdSpeed = FindSpeedStandardDeviation(month, year);
        const float madSpeed = FindSpeedMad(month, year);

        const float meanTemp = FindTemperatureMean(month, year);
        const float sdTemp = FindTemperatureStandardDeviation(month, year);
        const float madTemp = FindTemperatureMad(month, year);

        const float totalSolar = FindTotalSolar(month, year);

        out << ConvertMonth(month) << ",";

        if (hasWind)
        {
            out << (meanSpeed * 3.6f) << "("
                << (sdSpeed * 3.6f) << ", "
                << (madSpeed * 3.6f) << ")";
        }

        out << ",";

        if (hasTemp)
        {
            out << meanTemp << "("
                << sdTemp << ", "
                << madTemp << ")";
        }

        out << ",";

        if (hasSolar)
        {
            out << totalSolar;
        }

        out << "\n";
    }

    if (!hasAnyData)
    {
        out << "No Data\n";
    }

    out.close();
}
