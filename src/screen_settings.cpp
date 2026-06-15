#include <Arduino.h>
#include <lvgl.h>

#include "screen_settings.h"

void screen_settings_create()
{
    Serial.println("Settings Screen erstellt");

    lv_obj_t* screen = lv_scr_act();

    lv_obj_t* title = lv_label_create(screen);

    lv_label_set_text(
        title,
        "SETTINGS\n\nDisplay\nCalibration\nSystem\nAbout"
    );
    lv_label_set_text(
    title,
    "DIAGNOSTICS\n\nBMI270: OK\nDisplay: OK\nTouch: N/A\nBattery: N/A\nWiFi: N/A"
);
    lv_label_set_text(
    title,
    "BATTERY\n\nLevel: 100%%\nVoltage: 4.20V\nCharging: NO"
);

lv_label_set_text(
    title,
    "WIFI / OTA\n\nWiFi: DISCONNECTED\nIP: -\nOTA: READY"
);

    lv_obj_align(
        title,
        LV_ALIGN_CENTER,
        0,
        0
    );

}

void screen_settings_update()
{
}