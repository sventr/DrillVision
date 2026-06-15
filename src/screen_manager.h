#pragma once

enum class ScreenId
{
    Main,
    Calibration,
    Settings,
    Diagnostics,
    Battery,
    Wifi
};

void screen_manager_init();
void screen_manager_update();

void screen_manager_show(ScreenId screen);
void screen_manager_next();

ScreenId screen_manager_get_current();