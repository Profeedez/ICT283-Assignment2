// Menu.cpp
//
// Implementation of the Menu user-interface helper.
// Responsible for displaying prompts and collecting validated input.
//
// Version
// 01 01/03/2026 Heng Kiao Woon
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "Menu.h"
#include "Utility.h"
#include <iostream>
#include <string>

//----------------------------------------------------------------------------
// Function implementations

//----------------------------------------------------------------------------
// Default constructor.
Menu::Menu()
{
}

//----------------------------------------------------------------------------
// Displays the main menu options.
void Menu::DisplayMenu() const
{
    std::cout << "\n===== WEATHER MENU =====\n";
    std::cout << "1. Mean & Standard Deviation Wind Speed\n";
    std::cout << "2. Mean & Standard Deviation Temperature\n";
    std::cout << "3. Total Solar Radiation\n";
    std::cout << "4. Write Summary to File\n";
    std::cout << "5. Quit\n";
}

//----------------------------------------------------------------------------
// Prompts for and validates the menu choice (1-5).
int Menu::PromptChoice() const
{
    return GetValidIntegerLine("Enter choice (1-5): ", 1, 5);
}

//----------------------------------------------------------------------------
// Prompts for and validates a month (1-12).
int Menu::PromptMonth() const
{
    return GetValidIntegerLine("Enter month (1-12): ", 1, 12);
}

//----------------------------------------------------------------------------
// Prompts for and validates a year (0-9999).
int Menu::PromptYear() const
{
    return GetValidIntegerLine("Enter year: ", 0);
}

//----------------------------------------------------------------------------
// Helper that calls Utility input validation for integer ranges.
int Menu::GetValidIntegerLine(const char* prompt, int min, int max) const
{
    // Uses your Utility::Trim and ParseInt logic via GetValidInteger.
    // Keeping UI SRP: Menu asks Utility to validate.
    return GetValidInteger(prompt, min, max);
}

int Menu::GetValidIntegerLine(const char* prompt, int min) const
{
    return GetValidInteger(prompt, min);
}
