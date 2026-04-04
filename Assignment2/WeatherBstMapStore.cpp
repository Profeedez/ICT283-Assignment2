// WeatherBstMapStore.cpp
//
// Implementation of the WeatherBstMapStore class.
// Stores weather records using an outer BST of years,
// where each year node contains a map of monthly BSTs.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial WeatherBstMapStore implementation.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "WeatherBstMapStore.h"
#include "Calculator.h"
#include "Utility.h"

#include <fstream>
#include <iostream>

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
// File-local helper state and traversal callback functions
namespace
{
int g_targetYear = 0;
int g_targetMonth = 0;

const YearNode* g_foundYearNode = nullptr;

Vector<float>* g_speedValues = nullptr;
Vector<float>* g_temperatureValues = nullptr;
float g_totalSolar = 0.0f;

bool* g_hasValidWind = nullptr;
bool* g_hasValidTemperature = nullptr;
bool* g_hasValidSolar = nullptr;

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
// Collects valid speed values from a monthly BST.
void CollectSpeedValue(const WeatherRecType& record)
{
    const float speed = record.GetSpeed();

    if (speed >= 0.0f && g_speedValues != nullptr)
    {
        g_speedValues->Add(speed);
    }
}

//----------------------------------------------------------------------------
// Collects valid ambient temperature values from a monthly BST.
void CollectTemperatureValue(const WeatherRecType& record)
{
    const float temperature = record.GetAmbientTemperature();

    if (temperature >= 0.0f && g_temperatureValues != nullptr)
    {
        g_temperatureValues->Add(temperature);
    }
}

//----------------------------------------------------------------------------
// Accumulates solar radiation total from a monthly BST.
void CollectSolarTotal(const WeatherRecType& record)
{
    const float solar = record.GetSolarRadiation();

    if (solar >= 100.0f)
    {
        g_totalSolar += (solar * (1.0f / 6.0f)) / 1000.0f;
    }
}

//----------------------------------------------------------------------------
// Checks whether at least one valid wind value exists.
void CheckValidWind(const WeatherRecType& record)
{
    if (g_hasValidWind != nullptr && record.GetSpeed() >= 0.0f)
    {
        *g_hasValidWind = true;
    }
}

//----------------------------------------------------------------------------
// Checks whether at least one valid temperature value exists.
void CheckValidTemperature(const WeatherRecType& record)
{
    if (g_hasValidTemperature != nullptr &&
            record.GetAmbientTemperature() >= 0.0f)
    {
        *g_hasValidTemperature = true;
    }
}

//----------------------------------------------------------------------------
// Checks whether at least one valid solar radiation value exists.
void CheckValidSolar(const WeatherRecType& record)
{
    if (g_hasValidSolar != nullptr &&
            record.GetSolarRadiation() >= 100.0f)
    {
        *g_hasValidSolar = true;
    }
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
// Traverses each year node and, if the selected month exists, traverses that month BST.
void CollectSPCCFromYearNode(const YearNode& node)
{
    std::map<int, Bst<WeatherRecType> >::const_iterator monthIt =
        node.recordsByMonth.find(g_targetMonth);

    if (monthIt != node.recordsByMonth.end())
    {
        monthIt->second.inorderTraversal(CollectSPCCPairs);
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
// Finds a month BST inside a year node.
const Bst<WeatherRecType>* LocateMonthTree(const YearNode* yearNode, int month)
{
    if (yearNode == nullptr)
    {
        return nullptr;
    }

    std::map<int, Bst<WeatherRecType> >::const_iterator monthIt =
        yearNode->recordsByMonth.find(month);

    if (monthIt == yearNode->recordsByMonth.end())
    {
        return nullptr;
    }

    return &(monthIt->second);
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

    return yearNode->recordsByMonth[month].insert(record);
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
    const int month = record.GetDate().GetMonth();
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const Bst<WeatherRecType>* monthTree = LocateMonthTree(yearNode, month);

    if (monthTree == nullptr)
    {
        return false;
    }

    return monthTree->search(record);
}

//----------------------------------------------------------------------------
// Wind speed calculations
float WeatherBstMapStore::FindSpeedMean(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const Bst<WeatherRecType>* monthTree = LocateMonthTree(yearNode, month);

    if (monthTree == nullptr)
    {
        return 0.0f;
    }

    Vector<float> speedValues;
    g_speedValues = &speedValues;

    monthTree->inorderTraversal(CollectSpeedValue);

    g_speedValues = nullptr;

    if (speedValues.Size() == 0)
    {
        return 0.0f;
    }

    return calculateMean(speedValues);
}

float WeatherBstMapStore::FindSpeedStandardDeviation(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const Bst<WeatherRecType>* monthTree = LocateMonthTree(yearNode, month);

    if (monthTree == nullptr)
    {
        return 0.0f;
    }

    Vector<float> speedValues;
    g_speedValues = &speedValues;

    monthTree->inorderTraversal(CollectSpeedValue);

    g_speedValues = nullptr;

    if (speedValues.Size() < 2)
    {
        return 0.0f;
    }

    return calculateStandardDeviation(speedValues);
}

//----------------------------------------------------------------------------
// Temperature calculations
float WeatherBstMapStore::FindTemperatureMean(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const Bst<WeatherRecType>* monthTree = LocateMonthTree(yearNode, month);

    if (monthTree == nullptr)
    {
        return 0.0f;
    }

    Vector<float> temperatureValues;
    g_temperatureValues = &temperatureValues;

    monthTree->inorderTraversal(CollectTemperatureValue);

    g_temperatureValues = nullptr;

    if (temperatureValues.Size() == 0)
    {
        return 0.0f;
    }

    return calculateMean(temperatureValues);
}

float WeatherBstMapStore::FindTemperatureStandardDeviation(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const Bst<WeatherRecType>* monthTree = LocateMonthTree(yearNode, month);

    if (monthTree == nullptr)
    {
        return 0.0f;
    }

    Vector<float> temperatureValues;
    g_temperatureValues = &temperatureValues;

    monthTree->inorderTraversal(CollectTemperatureValue);

    g_temperatureValues = nullptr;

    if (temperatureValues.Size() < 2)
    {
        return 0.0f;
    }

    return calculateStandardDeviation(temperatureValues);
}

//----------------------------------------------------------------------------
// Solar radiation calculations
float WeatherBstMapStore::FindTotalSolar(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const Bst<WeatherRecType>* monthTree = LocateMonthTree(yearNode, month);

    if (monthTree == nullptr)
    {
        return 0.0f;
    }

    g_totalSolar = 0.0f;

    monthTree->inorderTraversal(CollectSolarTotal);

    return g_totalSolar;
}

//----------------------------------------------------------------------------
// Data presence checks
bool WeatherBstMapStore::HasValidWind(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const Bst<WeatherRecType>* monthTree = LocateMonthTree(yearNode, month);

    if (monthTree == nullptr)
    {
        return false;
    }

    bool hasValidWind = false;
    g_hasValidWind = &hasValidWind;

    monthTree->inorderTraversal(CheckValidWind);

    g_hasValidWind = nullptr;

    return hasValidWind;
}

bool WeatherBstMapStore::HasValidTemperature(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const Bst<WeatherRecType>* monthTree = LocateMonthTree(yearNode, month);

    if (monthTree == nullptr)
    {
        return false;
    }

    bool hasValidTemperature = false;
    g_hasValidTemperature = &hasValidTemperature;

    monthTree->inorderTraversal(CheckValidTemperature);

    g_hasValidTemperature = nullptr;

    return hasValidTemperature;
}

bool WeatherBstMapStore::HasValidSolar(int month, int year) const
{
    const YearNode* yearNode = LocateYearNode(m_yearTree, year);
    const Bst<WeatherRecType>* monthTree = LocateMonthTree(yearNode, month);

    if (monthTree == nullptr)
    {
        return false;
    }

    bool hasValidSolar = false;
    g_hasValidSolar = &hasValidSolar;

    monthTree->inorderTraversal(CheckValidSolar);

    g_hasValidSolar = nullptr;

    return hasValidSolar;
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

    out << "Month,Average Wind Speed(stdev),Average Ambient Temperature(stdev),Solar Radiation\n";

    for (int month = 1; month <= 12; ++month)
    {
        const bool hasWind = HasValidWind(month, year);
        const bool hasTemp = HasValidTemperature(month, year);
        const bool hasSolar = HasValidSolar(month, year);

        if (!hasWind && !hasTemp && !hasSolar)
        {
            continue;
        }

        const float meanSpeed = FindSpeedMean(month, year);
        const float sdSpeed = FindSpeedStandardDeviation(month, year);
        const float meanTemp = FindTemperatureMean(month, year);
        const float sdTemp = FindTemperatureStandardDeviation(month, year);
        const float totalSolar = FindTotalSolar(month, year);

        out << ConvertMonth(month) << ",";

        if (hasWind)
        {
            out << (meanSpeed * 3.6f) << "("
                << (sdSpeed * 3.6f) << ")";
        }
        out << ",";

        if (hasTemp)
        {
            out << meanTemp << "(" << sdTemp << ")";
        }
        out << ",";

        if (hasSolar)
        {
            out << totalSolar;
        }

        out << "\n";
    }

    out.close();
}
