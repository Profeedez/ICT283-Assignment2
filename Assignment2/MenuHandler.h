/**
 * @file MenuHandler.h
 * @brief Declares MenuHandler, the controller for the program menu loop.
 *
 * MenuHandler coordinates between:
 * - Menu (view): user input and menu display
 * - WeatherLogType (model): data storage and calculations
 *
 * @author Heng Kiao Woon
 * @version 01
 * @date 01/03/2026
 */

#ifndef MENUHANDLER_H_INCLUDED
#define MENUHANDLER_H_INCLUDED

#include "Menu.h"
#include "WeatherLogType.h"

/**
 * @class MenuHandler
 * @brief Controller: runs the menu loop and executes user-selected actions.
 */
class MenuHandler
{
public:
    /**
     * @brief Constructs a controller with references to the view and model.
     * @param menu Menu UI component.
     * @param log  Weather log/model containing loaded data.
     */
    MenuHandler(Menu& menu, const WeatherLogType& log);

    /**
     * @brief Runs the main menu loop until the user exits.
     */
    void Run();

private:
    Menu& m_menu;               /// UI component (view).
    const WeatherLogType& m_log; /// Data and computations (model).

    /**
     * @brief Handles menu option 1: wind speed mean and standard deviation.
     */
    void HandleOption1();

    /**
     * @brief Handles menu option 2: ambient temperature mean and standard deviation.
     */
    void HandleOption2();

    /**
     * @brief Handles menu option 3: total solar radiation for a month.
     */
    void HandleOption3();

    /**
     * @brief Handles menu option 4: exports a yearly summary to a CSV file.
     */
    void HandleOption4();

    /**
     * @brief Writes a summary CSV for the specified year.
     * @param year The year to export.
     */
    void ExportSummaryCSV(int year) const;
};

#endif // MENUHANDLER_H_INCLUDED
