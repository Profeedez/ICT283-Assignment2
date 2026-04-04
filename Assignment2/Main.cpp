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
 * - Uses WeatherBstMapStore as data model.
 *
 * @author
 * Heng Kiao Woon
 *
 * @version 03
 * @date 04/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial main program setup.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 * 03 04/04/2026 Heng Kiao Woon - Refactored to use BST store for Assignment 2.
 */

#include "Menu.h"
#include "MenuHandler.h"
#include "WeatherFileReader.h"
#include "WeatherBstMapStore.h"
#include <iostream>

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
    WeatherBstMapStore store;
    WeatherFileReader reader;

    std::cout << "Loading data...\n";

    reader.LoadFromConfig("data/data_source.txt", store);

    std::cout << "Data loaded successfully.\n\n";

    Menu menu;
    MenuHandler handler(menu, store);
    handler.Run();

    return 0;
}
