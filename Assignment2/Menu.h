/**
 * @file Menu.h
 * @brief Declares the Menu class for console-based user interaction.
 *
 * The Menu class is the view component of the application. It is responsible
 * for displaying prompts and collecting validated input values, while keeping
 * calculation logic outside the user-interface layer.
 *
 * @author Heng Kiao Woon
 * @version 02
 * @date 03/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial Menu class declaration
 * 02 03/04/2026 Heng Kiao Woon - Updated file header
 */

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/**
 * @class Menu
 * @brief View/UI component for displaying prompts and reading user choices.
 */
class Menu
{
public:
    /**
     * @brief Constructs a Menu instance.
     */
    Menu();

    /**
     * @brief Prints the main menu options to the console.
     */
    void DisplayMenu() const;

    /**
     * @brief Prompts the user for a menu choice.
     * @return The chosen option number.
     */
    int  PromptChoice() const;

    /**
     * @brief Prompts the user for a month (1-12).
     * @return The month number.
     */
    int  PromptMonth() const;

    /**
     * @brief Prompts the user for a year value.
     * @return The year.
     */
    int  PromptYear() const;

private:
    /**
     * @brief Reads an integer value from the console with bounds checking.
     * @param prompt Text shown to the user.
     * @param min Minimum accepted value (inclusive).
     * @param max Maximum accepted value (inclusive).
     * @return A validated integer in the range [min, max].
     */
    int GetValidIntegerLine(const char* prompt, int min, int ) const;
    int GetValidIntegerLine(const char* prompt, int min ) const;
};

#endif // MENU_H_INCLUDED
