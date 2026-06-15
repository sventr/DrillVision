#include "screen_manager.h"

#include "screen_main.h"
#include "screen_calibration.h"
#include "screen_settings.h"
#include "screen_diagnostics.h"
#include "screen_battery.h"
#include "screen_wifi.h"
#include <lvgl.h>

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

        case ScreenId::Settings:
            screen_settings_update();
            break;

        case ScreenId::Diagnostics:
            screen_diagnostics_update();
            break;

        case ScreenId::Battery:
            screen_battery_update();
            break;

        case ScreenId::Wifi:
            screen_wifi_update();
            break;
    }
}

void screen_manager_show(ScreenId screen)
{
    currentScreen = screen;

    lv_obj_clean(lv_scr_act());

    switch (currentScreen)
    {
        case ScreenId::Main:
            screen_main_create();
            break;

        case ScreenId::Calibration:
            screen_calibration_create();
            break;

        case ScreenId::Settings:
            screen_settings_create();
            break;

        case ScreenId::Diagnostics:
            screen_diagnostics_create();
            break;

        case ScreenId::Battery:
            screen_battery_create();
            break;

        case ScreenId::Wifi:
            screen_wifi_create();
            break;
    }
}

void screen_manager_next()
{
    switch (currentScreen)
    {
        case ScreenId::Main:
            screen_manager_show(ScreenId::Calibration);
            break;

        case ScreenId::Calibration:
            screen_manager_show(ScreenId::Settings);
            break;

        case ScreenId::Settings:
            screen_manager_show(ScreenId::Diagnostics);
            break;

        case ScreenId::Diagnostics:
            screen_manager_show(ScreenId::Battery);
            break;

        case ScreenId::Battery:
            screen_manager_show(ScreenId::Wifi);
            break;

        case ScreenId::Wifi:
            screen_manager_show(ScreenId::Main);
            break;
    }
}

ScreenId screen_manager_get_current()
{
    return currentScreen;
}