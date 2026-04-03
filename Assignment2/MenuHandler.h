/**
 * @file MenuHandler.h
 * @brief Declares the MenuHandler controller for the weather statistics program.
 *
 * MenuHandler coordinates between the Menu view and the weather data model. It
 * runs the main menu loop and dispatches each option to the appropriate
 * calculation or export behaviour.
 *
 * @author Heng Kiao Woon
 * @version 02
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial MenuHandler declaration.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 */

#ifndef MENUHANDLER_H_INCLUDED
#define MENUHANDLER_H_INCLUDED

#include "Menu.h"

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
     */

    /**
     * @brief Runs the main menu loop until the user exits.
     */
    void Run();

private:
    Menu& m_menu;               /// UI component (view).

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

    };

#endif // MENUHANDLER_H_INCLUDED
