// Menu.cpp
//
// Implementation of the Menu user-interface class.
// Displays menu text, prompts the user for input, and delegates validation to shared helpers.
//
// Version
// 01 01/03/2026 Heng Kiao Woon - Initial Menu class implementation.
// 02 03/04/2026 Heng Kiao Woon - Updated file header.
// 03 04/04/2026 Heng Kiao Woon - Updated menu text
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Menu.h"
#include "Utility.h"

#include <iostream>

//----------------------------------------------------------------------------
// Constructors
Menu::Menu()
{
}

//----------------------------------------------------------------------------
// Displays the main menu options.
void Menu::DisplayMenu() const
{
    std::cout << "\n===== WEATHER MENU =====\n";
    std::cout << "1. Average wind speed and sample standard deviation for a specified month and year\n";
    std::cout << "2. Average ambient air temperature and sample standard deviation for each month of a specified year\n";
    std::cout << "3. Sample Pearson Correlation Coefficient for a specified month across all loaded years\n";
    std::cout << "4. Export yearly WindTempSolar.csv summary\n";
    std::cout << "5. Exit\n";
}

//----------------------------------------------------------------------------
// Prompts for and validates the menu choice.
int Menu::PromptChoice() const
{
    return GetValidIntegerLine("Enter choice (1-5): ", 1, 5);
}

//----------------------------------------------------------------------------
// Prompts for and validates a month.
int Menu::PromptMonth() const
{
    return GetValidIntegerLine("Enter month (1-12): ", 1, 12);
}

//----------------------------------------------------------------------------
// Prompts for and validates a year.
int Menu::PromptYear() const
{
    return GetValidIntegerLine("Enter year: ", 0);
}

//----------------------------------------------------------------------------
// Reads an integer within a given inclusive range.
int Menu::GetValidIntegerLine(const char* prompt, int min, int max) const
{
    return GetValidInteger(prompt, min, max);
}

//----------------------------------------------------------------------------
// Reads an integer greater than or equal to a minimum value.
int Menu::GetValidIntegerLine(const char* prompt, int min) const
{
    return GetValidInteger(prompt, min);
}
