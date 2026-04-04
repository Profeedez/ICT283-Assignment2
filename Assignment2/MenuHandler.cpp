//
// MenuHandler.cpp
//
// Implementation of the MenuHandler controller.
// Connects menu selections to weather calculations and export features in the program.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial MenuHandler implementation.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
// 03 04/04/2026 Heng Kiao Woon - Refactored for  BST store and sPCC.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "MenuHandler.h"
#include "Utility.h"
#include "Calculator.h"
#include <fstream>
#include <iostream>

//----------------------------------------------------------------------------
// Constructor

MenuHandler::MenuHandler(Menu& menu, const WeatherBstMapStore& store)
    : m_menu(menu), m_store(store)
{
}

//----------------------------------------------------------------------------
// Runs the menu loop and dispatches options.
void MenuHandler::Run()
{
    int choice = 0;

    do
    {
        m_menu.DisplayMenu();
        choice = m_menu.PromptChoice();

        switch (choice)
        {
        case 1:
            HandleOption1();
            break;
        case 2:
            HandleOption2();
            break;
        case 3:
            HandleOption3();
            break;
        case 4:
            HandleOption4();
            break;
        case 5:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }
    while (choice != 5);
}

//----------------------------------------------------------------------------
// Handles option 1: mean and sample standard deviation of wind speed.
void MenuHandler::HandleOption1()
{
    const int month = m_menu.PromptMonth();
    const int year = m_menu.PromptYear();

    if (!m_store.HasValidWind(month, year))
    {
        std::cout << ConvertMonth(month) << " " << year << ": No Data\n";
        return;
    }

    const float meanMs = m_store.FindSpeedMean(month, year);
    const float standardDeviationMs = m_store.FindSpeedStandardDeviation(month, year);

    std::cout << ConvertMonth(month) << " " << year << ":\n";
    std::cout << "Average speed: " << (meanMs * 3.6f) << " km/h\n";
    std::cout << "Sample stdev: " << (standardDeviationMs * 3.6f) << "\n";
}

//----------------------------------------------------------------------------
// Handles option 2: mean and sample standard deviation of temperature for each month.
void MenuHandler::HandleOption2()
{
    const int year = m_menu.PromptYear();

    std::cout << year << "\n";

    for (int month = 1; month <= 12; ++month)
    {
        if (!m_store.HasValidTemperature(month, year))
        {
            std::cout << ConvertMonth(month) << ": No Data\n";
            continue;
        }

        const float meanTemperature = m_store.FindTemperatureMean(month, year);
        const float standardDeviationTemperature =
            m_store.FindTemperatureStandardDeviation(month, year);

        std::cout << ConvertMonth(month)
                  << ": average: " << meanTemperature
                  << " degrees C, stdev: " << standardDeviationTemperature
                  << "\n";
    }
}

//----------------------------------------------------------------------------
// Handles option 3: sPCC for a selected month and two user-selected fields.
void MenuHandler::HandleOption3()
{
    const int month = m_menu.PromptMonth();
    const int year = m_menu.PromptYear();

    std::cout << "Choose first data field:\n";
    const DataField firstField = PromptFieldSelection("Enter first field choice: ");

    DataField secondField;
    do
    {
        std::cout << "Choose second data field:\n";
        secondField = PromptFieldSelection("Enter second field choice: ");

        if (secondField == firstField)
        {
            std::cout << "Please choose two different fields.\n";
        }
    }
    while (secondField == firstField);

    const Vector<float> firstValues = CollectFieldData(month, year, firstField);
    const Vector<float> secondValues = CollectFieldData(month, year, secondField);

    if (firstValues.getSize() == 0 || secondValues.getSize() == 0)
    {
        std::cout << ConvertMonth(month) << " " << year << ": No Data\n";
        return;
    }

    if (firstValues.getSize() != secondValues.getSize())
    {
        std::cout << "Unable to calculate sPCC: data series sizes do not match.\n";
        return;
    }

    if (firstValues.getSize() < 2)
    {
        std::cout << "Unable to calculate sPCC: at least two paired values are required.\n";
        return;
    }

    const float coefficient = Calculator::sPCC(firstValues, secondValues);

    std::cout << ConvertMonth(month) << " " << year << "\n";
    std::cout << "sPCC(" << GetFieldName(firstField)
              << ", " << GetFieldName(secondField)
              << ") = " << coefficient << "\n";
}

//----------------------------------------------------------------------------
// Handles option 4: export yearly summary to CSV.
void MenuHandler::HandleOption4()
{
    const int year = m_menu.PromptYear();
    ExportSummaryCSV(year);
}

//----------------------------------------------------------------------------
// Writes WindTempSolar.csv with blanks for missing fields.
void MenuHandler::ExportSummaryCSV(int year) const
{
    std::ofstream outputFile("WindTempSolar.csv");
    if (!outputFile.is_open())
    {
        std::cout << "Failed to create WindTempSolar.csv\n";
        return;
    }

    outputFile << year << "\n";
    outputFile << "Month,Average Wind Speed(stdev),Average Ambient Temperature(stdev),Solar Radiation\n";

    bool hasAnyData = false;

    for (int month = 1; month <= 12; ++month)
    {
        const bool hasWind = m_store.HasValidWind(month, year);
        const bool hasTemperature = m_store.HasValidTemperature(month, year);
        const bool hasSolar = m_store.HasValidSolar(month, year);

        if (!hasWind && !hasTemperature && !hasSolar)
        {
            continue;
        }

        hasAnyData = true;

        outputFile << ConvertMonth(month) << ",";

        if (hasWind)
        {
            const float meanWindKmh = m_store.FindSpeedMean(month, year) * 3.6f;
            const float standardDeviationWindKmh =
                m_store.FindSpeedStandardDeviation(month, year) * 3.6f;

            outputFile << meanWindKmh << "(" << standardDeviationWindKmh << ")";
        }

        outputFile << ",";

        if (hasTemperature)
        {
            const float meanTemperature = m_store.FindTemperatureMean(month, year);
            const float standardDeviationTemperature =
                m_store.FindTemperatureStandardDeviation(month, year);

            outputFile << meanTemperature << "(" << standardDeviationTemperature << ")";
        }

        outputFile << ",";

        if (hasSolar)
        {
            const float totalSolar = m_store.FindTotalSolar(month, year);
            outputFile << totalSolar;
        }

        outputFile << "\n";
    }

    if (!hasAnyData)
    {
        outputFile << "No Data\n";
    }

    outputFile.close();
    std::cout << "Exported to WindTempSolar.csv\n";
}

//----------------------------------------------------------------------------
// Prompts the user to choose a field for sPCC.
MenuHandler::DataField MenuHandler::PromptFieldSelection(const char* promptText) const
{
    int choice = 0;

    do
    {
        std::cout << "1. Average Wind Speed (S)\n";
        std::cout << "2. Ambient Air Temperature (T)\n";
        std::cout << "3. Solar Radiation (SR)\n";
        std::cout << promptText;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = 0;
        }

        if (choice < 1 || choice > 3)
        {
            std::cout << "Invalid field choice. Please enter 1, 2, or 3.\n";
        }
    }
    while (choice < 1 || choice > 3);

    return static_cast<DataField>(choice);
}

//----------------------------------------------------------------------------
// Collects monthly data for the selected field.
Vector<float> MenuHandler::CollectFieldData(int month, int year, DataField field) const
{
    Vector<float> values;

    switch (field)
    {
    case FIELD_SPEED:
        m_store.GetSpeedDataForMonth(month, year, values);
        break;

    case FIELD_TEMPERATURE:
        m_store.GetTemperatureDataForMonth(month, year, values);
        break;

    case FIELD_SOLAR:
        m_store.GetSolarDataForMonth(month, year, values);
        break;

    default:
        break;
    }

    return values;
}

//----------------------------------------------------------------------------
// Returns the display name of a field.
const char* MenuHandler::GetFieldName(DataField field) const
{
    switch (field)
    {
    case FIELD_SPEED:
        return "Average Wind Speed";
    case FIELD_TEMPERATURE:
        return "Ambient Air Temperature";
    case FIELD_SOLAR:
        return "Solar Radiation";
    default:
        return "Unknown Field";
    }
}
