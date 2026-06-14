#include "screen_manager.h"

#include "screen_main.h"
#include "screen_calibration.h"

static ScreenId currentScreen = ScreenId::Main;

void screen_manager_init()
{
    currentScreen = ScreenId::Main;
    screen_main_create();
}

void screen_manager_update()
{
    switch (currentScreen)
    {
        case ScreenId::Main:
            screen_main_update();
            break;

        case ScreenId::Calibration:
            screen_calibration_update();
            break;
    }
}

void screen_manager_show(ScreenId screen)
{
    currentScreen = screen;

    switch (currentScreen)
    {
        case ScreenId::Main:
            screen_main_create();
            break;

        case ScreenId::Calibration:
            screen_calibration_create();
            break;
    }
}

ScreenId screen_manager_get_current()
{
    return currentScreen;
}
void screen_manager_next()
{
    switch (currentScreen)
    {
        case ScreenId::Main:
            screen_manager_show(ScreenId::Calibration);
            break;

        case ScreenId::Calibration:
            screen_manager_show(ScreenId::Main);
            break;
    }
}