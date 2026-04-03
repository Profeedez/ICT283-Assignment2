/**
 * @file Menu.h
 * @brief Declares the Menu class (console UI helper).
 *
 * Menu is responsible only for user interaction:
 * - displaying the available options
 * - prompting and validating user input values
 *
 * It does not perform any weather calculations.
 *
 * @author Heng Kiao Woon
 * @version 01
 * @date 01/03/2026
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
