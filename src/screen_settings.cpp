#include <Arduino.h>
#include <lvgl.h>

#include "screen_settings.h"

void screen_settings_create()
{
    Serial.println("Settings Screen erstellt");

    lv_obj_t* screen = lv_scr_act();

    lv_obj_t* title = lv_label_create(screen);
    lv_label_set_text(title, "SETTINGS");
    lv_obj_align(title, LV_ALIGN_CENTER, 0, 0);
}

void screen_settings_update()
{
}