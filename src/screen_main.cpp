#include <Arduino.h>
#include <lvgl.h>

#include "screen_main.h"
#include "ui_model.h"
#include "system_state.h"
#include "config.h"

static lv_obj_t* labelTitle = nullptr;
static lv_obj_t* labelVersion = nullptr;
static lv_obj_t* labelX = nullptr;
static lv_obj_t* labelY = nullptr;
static lv_obj_t* labelBattery = nullptr;
static lv_obj_t* labelStatus = nullptr;

void screen_main_create()
{
    Serial.println("Main Screen LVGL erstellt");

    lv_obj_t* screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);

    labelTitle = lv_label_create(screen);
    lv_label_set_text(labelTitle, "BOHRVISION");
    lv_obj_align(labelTitle, LV_ALIGN_TOP_MID, 0, 45);

    labelVersion = lv_label_create(screen);
    lv_label_set_text(labelVersion, PROJECT_VERSION);
    lv_obj_align(labelVersion, LV_ALIGN_TOP_MID, 0, 75);

    labelX = lv_label_create(screen);
    lv_label_set_text(labelX, "X: 0.00°");
    lv_obj_align(labelX, LV_ALIGN_LEFT_MID, 45, 0);

    labelY = lv_label_create(screen);
    lv_label_set_text(labelY, "Y: 0.00°");
    lv_obj_align(labelY, LV_ALIGN_BOTTOM_MID, 0, -75);

    labelBattery = lv_label_create(screen);
    lv_label_set_text(labelBattery, "BAT: 100%");
    lv_obj_align(labelBattery, LV_ALIGN_TOP_MID, 0, 115);

    labelStatus = lv_label_create(screen);
    lv_label_set_text(labelStatus, "STARTUP");
    lv_obj_align(labelStatus, LV_ALIGN_BOTTOM_MID, 0, -35);
}

void screen_main_update()
{
    if (!labelX || !labelY || !labelBattery || !labelStatus)
    {
        return;
    }

    char buffer[64];

    snprintf(buffer, sizeof(buffer), "X: %.2f°", g_uiData.xAngle);
    lv_label_set_text(labelX, buffer);

    snprintf(buffer, sizeof(buffer), "Y: %.2f°", g_uiData.yAngle);
    lv_label_set_text(labelY, buffer);

    snprintf(buffer, sizeof(buffer), "BAT: %.0f%%", g_uiData.batteryPercent);
    lv_label_set_text(labelBattery, buffer);

    lv_label_set_text(labelStatus, system_state_to_text(g_uiData.state));
}