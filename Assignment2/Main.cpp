/**
 * @file Main.cpp
 * @brief Entry point of the weather statistics program.
 *
 * This file initializes the core components of the system,
 * loads weather data from the configured source file, and
 * starts the menu-driven user interface.
 *
 * Design:
 * - Uses Menu for UI display.
 * - Uses MenuHandler as controller.
 *
 * @author
 * Heng Kiao Woon
 *
 * @version 02
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial main program setup.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 */

#include "WeatherLogType.h"
#include "Menu.h"
#include "MenuHandler.h"
#include "WeatherFileReader.h"

/**
 * @brief Main function of the program.
 *
 * Creates required objects, loads weather data,
 * and starts the menu loop.
 *
 * @return int Returns 0 upon successful execution.
 */
int main()
{

    WeatherFileReader weatherFileReader;
    weatherFileReader.LoadFromConfig(log);

    Menu menu;
    MenuHandler handler(menu, log);
    handler.Run();

    return 0;
}
