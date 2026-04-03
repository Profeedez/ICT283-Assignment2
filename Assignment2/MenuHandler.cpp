// MenuHandler.cpp
//
// Implementation of the MenuHandler controller.
// Connects menu selections to weather calculations and export features in the program.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial MenuHandler implementation.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "MenuHandler.h"
#include "Utility.h"
#include <fstream>

//----------------------------------------------------------------------------
// Function implementations

//----------------------------------------------------------------------------
// Constructs a handler that connects the menu UI to .


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
// Handles option 1: mean and S.D. wind speed for a selected month/year.
void MenuHandler::HandleOption1()
{
    int month = m_menu.PromptMonth();
    int year  = m_menu.PromptYear();

    if (!m_log.HasValidWind(month, year))
    {
        std::cout << ConvertMonth(month) << " " << year << ": No Data\n";
        return;
    }

    float meanMs = m_log.FindSpeedMean(month, year);
    float sdMs   = m_log.FindSpeedStandardDeviation(month, year);

    std::cout << ConvertMonth(month) << " " << year << ":\n";
    std::cout << "Average speed: " << (meanMs * 3.6f) << " km/h\n";
    std::cout << "Standard Deviation: " << (sdMs * 3.6f) << "\n";
}

//----------------------------------------------------------------------------
// Handles option 2: mean and S.D. temperature for each month in a year.
void MenuHandler::HandleOption2()
{
    int year = m_menu.PromptYear();
    std::cout << year << "\n";

    for (int month = 1; month <= 12; ++month)
    {
        if (!m_log.HasValidTemperature(month, year))
        {
            std::cout << ConvertMonth(month) << ": No Data\n";
            continue;
        }

        float mean = m_log.FindTemperatureMean(month, year);
        float sd   = m_log.FindTemperatureStandardDeviation(month, year);

        std::cout << ConvertMonth(month) << ": " << mean << " (" << sd << ")\n";
    }
}

//----------------------------------------------------------------------------
// Handles option 3: total solar radiation for each month in a year.
void MenuHandler::HandleOption3()
{
    // This is correct per assignment: totals in kWh/m^2
    int year = m_menu.PromptYear();
    std::cout << year << "\n";

    for (int month = 1; month <= 12; ++month)
    {
        if (!m_log.HasValidSolar(month, year))
        {
            std::cout << ConvertMonth(month) << ": No Data\n";
            continue;
        }

        float total = m_log.FindTotalSolar(month, year);
        std::cout << ConvertMonth(month) << ": " << total << " kWh/m2\n";
    }
}

//----------------------------------------------------------------------------
// Handles option 4: export yearly summary to CSV.
void MenuHandler::HandleOption4()
{
    int year = m_menu.PromptYear();
    ExportSummaryCSV(year);
}

//----------------------------------------------------------------------------
// Writes WindTempSolar.csv with blanks for missing fields.
void MenuHandler::ExportSummaryCSV(int year) const
{
    std::ofstream out("data/WindTempSolar.csv");
    if (!out.is_open())
    {
        std::cout << "Failed to create WindTempSolar.csv\n";
        return;
    }

    // Line 1: year
    out << year << "\n";

    // Check if the entire year has ANY data at all
    bool anyYearData = false;
    for (int month = 1; month <= 12; ++month)
    {
        if (m_log.HasValidWind(month, year) ||
                m_log.HasValidTemperature(month, year) ||
                m_log.HasValidSolar(month, year))
        {
            anyYearData = true;
            break;
        }
    }

    if (!anyYearData)
    {
        out << "No Data\n";
        out.close();
        std::cout << "Exported to WindTempSolar.csv\n";
        return;
    }

    // Header (comma-separated)
    out << "Month, Average Wind Speed(stdev), Average Ambient Temperature(stdev), Solar Radiation\n";

    for (int month = 1; month <= 12; ++month)
    {
        bool hasWind  = m_log.HasValidWind(month, year);
        bool hasTemp  = m_log.HasValidTemperature(month, year);
        bool hasSolar = m_log.HasValidSolar(month, year);

        // If month has NO data for ALL fields -> skip month completely
        if (!hasWind && !hasTemp && !hasSolar)
            continue;

        out << ConvertMonth(month) << ",";

        // Wind field (blank if missing)
        if (hasWind)
        {
            float meanMs = m_log.FindSpeedMean(month, year);
            float sdMs   = m_log.FindSpeedStandardDeviation(month, year);
            out << (meanMs * 3.6f) << "(" << (sdMs * 3.6f) << ")";
        }
        out << ",";

        // Temperature field (blank if missing)
        if (hasTemp)
        {
            float mean = m_log.FindTemperatureMean(month, year);
            float sd   = m_log.FindTemperatureStandardDeviation(month, year);
            out << mean << "(" << sd << ")";
        }
        out << ",";

        // Solar field (blank if missing)
        if (hasSolar)
        {
            float total = m_log.FindTotalSolar(month, year);
            out << total;
        }

        out << "\n";
    }

    out.close();
    std::cout << "Exported to WindTempSolar.csv\n";
}
