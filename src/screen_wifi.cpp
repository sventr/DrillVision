#include <Arduino.h>
#include <lvgl.h>

#include "screen_wifi.h"

void screen_wifi_create()
{
    Serial.println("WiFi Screen erstellt");

    lv_obj_t* screen = lv_scr_act();

    lv_obj_t* title = lv_label_create(screen);
    lv_label_set_text(title, "WIFI / OTA");
    lv_obj_align(title, LV_ALIGN_CENTER, 0, 0);
}

void screen_wifi_update()
{
}