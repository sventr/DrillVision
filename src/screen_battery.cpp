#include <Arduino.h>
#include <lvgl.h>

#include "screen_battery.h"

void screen_battery_create()
{
    Serial.println("Battery Screen erstellt");

    lv_obj_t* screen = lv_scr_act();

    lv_obj_t* title = lv_label_create(screen);
    lv_label_set_text(title, "BATTERY");
    lv_obj_align(title, LV_ALIGN_CENTER, 0, 0);
}

void screen_battery_update()
{
}