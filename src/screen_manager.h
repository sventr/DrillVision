#pragma once

enum class ScreenId
{
    Main,
    Calibration
};

void screen_manager_init();
void screen_manager_update();

void screen_manager_show(ScreenId screen);
ScreenId screen_manager_get_current();