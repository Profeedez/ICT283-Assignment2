// Main.cpp
//
// Application entry point.
// Loads weather data and runs the menu handler.
//
// Version
// 02 01/03/2026 Heng Kiao Woon
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include "WeatherLogType.h"
#include "Menu.h"
#include "MenuHandler.h"
#include "WeatherFileReader.h"

//----------------------------------------------------------------------------
// Program entry point: loads data and starts the menu loop.
int main()
{
    WeatherLogType log;

    WeatherFileReader weatherFileReader;
    weatherFileReader.LoadFromConfig(log);

    Menu menu;
    MenuHandler handler(menu, log);
    handler.Run();

    return 0;
}
