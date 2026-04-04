/**
 * @file MenuHandler.h
 * @brief Declares the MenuHandler controller for the weather statistics program.
 *
 * MenuHandler coordinates between the Menu view and the weather data model. It
 * runs the main menu loop and dispatches each option to the appropriate
 * calculation or export behaviour.
 *
 * Assignment 2 notes:
 * - Uses WeatherBstMapStore instead of WeatherLogType.
 * - Option 3 performs sPCC calculation for the selected month applies to all years that have been loaded.
 *
 * @author Heng Kiao Woon
 * @version 04
 * @date 04/04/2026
 */

#ifndef MENUHANDLER_H_INCLUDED
#define MENUHANDLER_H_INCLUDED

#include "Menu.h"
#include "WeatherBstMapStore.h"

class MenuHandler
{
public:
    MenuHandler(Menu& menu, const WeatherBstMapStore& store);
    void Run();

private:
    Menu& m_menu;
    const WeatherBstMapStore& m_store;

    void HandleOption1();
    void HandleOption2();
    void HandleOption3();
    void HandleOption4();
};

#endif // MENUHANDLER_H_INCLUDED
