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
 * - Option 3 performs sPCC calculation for a selected month/year and two fields.
 *
 * @author Heng Kiao Woon
 * @version 03
 * @date 04/04/2026
 *
 * Version History:
 * 01 01/03/2026 Heng Kiao Woon - Initial MenuHandler declaration.
 * 02 03/04/2026 Heng Kiao Woon - Updated file header.
 * 03 04/04/2026 Heng Kiao Woon - Refactored for  BST store and sPCC.
 */

#ifndef MENUHANDLER_H_INCLUDED
#define MENUHANDLER_H_INCLUDED

#include "Menu.h"
#include "WeatherBstMapStore.h"
#include "Vector.h"

/**
 * @class MenuHandler
 * @brief Controller that runs the menu loop and executes user-selected actions.
 */
class MenuHandler
{
public:
    /**
     * @brief Constructs a controller with references to the view and model.
     * @param menu Menu UI component.
     * @param store Weather data store component.
     */
    MenuHandler(Menu& menu, const WeatherBstMapStore& store);

    /**
     * @brief Runs the main menu loop until the user exits.
     */
    void Run();

private:
    /**
     * @brief Identifies a supported weather field for sPCC and extraction.
     */
    enum DataField
    {
        FIELD_SPEED = 1,
        FIELD_TEMPERATURE = 2,
        FIELD_SOLAR = 3
    };

    Menu& m_menu;                           ///< UI component (view).
    const WeatherBstMapStore& m_store;      ///< Weather data model.

    /**
     * @brief Handles menu option 1: wind speed mean and sample standard deviation.
     */
    void HandleOption1();

    /**
     * @brief Handles menu option 2: ambient temperature mean and sample standard deviation.
     */
    void HandleOption2();

    /**
     * @brief Handles menu option 3: sample Pearson correlation coefficient for two fields.
     */
    void HandleOption3();

    /**
     * @brief Handles menu option 4: exports a yearly summary CSV file.
     */
    void HandleOption4();

    /**
     * @brief Writes the yearly summary CSV file.
     * @param year Selected year.
     */
    void ExportSummaryCSV(int year) const;

    /**
     * @brief Prompts the user to choose a field for sPCC.
     * @param promptText Prompt shown to the user.
     * @return Selected DataField.
     */
    DataField PromptFieldSelection(const char* promptText) const;

    /**
     * @brief Extracts monthly values for the selected field.
     * @param month Selected month.
     * @param year Selected year.
     * @param field Selected field type.
     * @return Vector of values for that month/year/field.
     */
    Vector<float> CollectFieldData(int month, int year, DataField field) const;

    /**
     * @brief Returns the display name of a field.
     * @param field Selected field type.
     * @return Field display text.
     */
    const char* GetFieldName(DataField field) const;
};

#endif // MENUHANDLER_H_INCLUDED
