#include <Arduino.h>
#include <lvgl.h>

#include "screen_diagnostics.h"

void screen_diagnostics_create()
{
    Serial.println("Diagnostics Screen erstellt");

    lv_obj_t* screen = lv_scr_act();

    lv_obj_t* title = lv_label_create(screen);
    lv_label_set_text(title, "DIAGNOSTICS");
    lv_obj_align(title, LV_ALIGN_CENTER, 0, 0);
}

void screen_diagnostics_update()
{
}