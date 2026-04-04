//
// MenuHandler.cpp
//
// Implementation of the MenuHandler controller.
// Connects menu selections to weather calculations and export features in the program.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial MenuHandler implementation.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
// 03 04/04/2026 Heng Kiao Woon - Refactored for BST store and sPCC.
// 04 04/04/2026 Heng Kiao Woon - Aligned with WeatherBstMapStore interface.
//---------------------------------------------------------------------------------

#include "MenuHandler.h"
#include "Utility.h"
#include "Calculator.h"
#include <iostream>

MenuHandler::MenuHandler(Menu& menu, const WeatherBstMapStore& store)
    : m_menu(menu), m_store(store)
{
}

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
    std::cout << "Average speed: " << ConvertMsToKmh(meanMs) << " km/h\n";
    std::cout << "Sample stdev: " << ConvertMsToKmh(standardDeviationMs) << "\n";
}

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

void MenuHandler::HandleOption3()
{
    const int month = m_menu.PromptMonth();

    float s_t = 0.0f;
    float s_r = 0.0f;
    float t_r = 0.0f;

    m_store.FindSPCCForMonthAllYears(month, s_t, s_r, t_r);

    if (absoluteValue(s_t) < 0.00001f)
    {
        s_t = 0.0f;
    }

    if (absoluteValue(s_r) < 0.00001f)
    {
        s_r = 0.0f;
    }

    if (absoluteValue(t_r) < 0.00001f)
    {
        t_r = 0.0f;
    }

    std::cout << "Sample Pearson Correlation Coefficient for "
              << ConvertMonth(month) << "\n";
    std::cout << "S_T: " << s_t << "\n";
    std::cout << "S_R: " << s_r << "\n";
    std::cout << "T_R: " << t_r << "\n";
}

void MenuHandler::HandleOption4()
{
    const int year = m_menu.PromptYear();
    m_store.ExportSummaryCSV(year, "data/WindTempSolar.csv");
    std::cout << "Exported to WindTempSolar.csv\n";
}
