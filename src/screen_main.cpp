#include <Arduino.h>
#include <lvgl.h>

#include "screen_main.h"
#include "ui_model.h"
#include "system_state.h"
#include "config.h"

static lv_obj_t* labelTitle = nullptr;
static lv_obj_t* labelVersion = nullptr;
static lv_obj_t* labelStatusBar = nullptr;
static lv_obj_t* labelX = nullptr;
static lv_obj_t* labelY = nullptr;
static lv_obj_t* labelStatus = nullptr;

static lv_color_t get_state_color(SystemState state)
{
    switch (state)
    {
        case SystemState::InLevel:
            return lv_color_hex(0x00FF66);
        case SystemState::Warning:
            return lv_color_hex(0xFFCC00);
        case SystemState::Alarm:
            return lv_color_hex(0xFF3300);
        default:
            return lv_color_hex(0xFFFFFF);
    }
}

void screen_main_create()
{
    Serial.println("Main Screen LVGL erstellt");

    lv_obj_t* screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);

    labelTitle = lv_label_create(screen);
    lv_label_set_text(labelTitle, "BOHRVISION");
    lv_obj_set_style_text_color(labelTitle, lv_color_hex(0x00FF66), 0);
    lv_obj_align(labelTitle, LV_ALIGN_TOP_MID, 0, 40);

    labelVersion = lv_label_create(screen);
    lv_label_set_text(labelVersion, PROJECT_VERSION);
    lv_obj_set_style_text_color(labelVersion, lv_color_white(), 0);
    lv_obj_align(labelVersion, LV_ALIGN_TOP_MID, 0, 70);

    labelStatusBar = lv_label_create(screen);
    lv_label_set_text(labelStatusBar, "WiFi:OFF  USB:ON  BAT:100%");
    lv_obj_set_style_text_color(labelStatusBar, lv_color_white(), 0);
    lv_obj_align(labelStatusBar, LV_ALIGN_TOP_MID, 0, 110);

    labelX = lv_label_create(screen);
    lv_label_set_text(labelX, "X: 0.00°");
    lv_obj_set_style_text_color(labelX, lv_color_white(), 0);
    lv_obj_align(labelX, LV_ALIGN_LEFT_MID, 45, 0);

    labelY = lv_label_create(screen);
    lv_label_set_text(labelY, "Y: 0.00°");
    lv_obj_set_style_text_color(labelY, lv_color_white(), 0);
    lv_obj_align(labelY, LV_ALIGN_BOTTOM_MID, 0, -75);

    labelStatus = lv_label_create(screen);
    lv_label_set_text(labelStatus, "STARTUP");
    lv_obj_set_style_text_color(labelStatus, lv_color_white(), 0);
    lv_obj_align(labelStatus, LV_ALIGN_BOTTOM_MID, 0, -35);
}

void screen_main_update()
{
    if (!labelX || !labelY || !labelStatusBar || !labelStatus)
    {
        return;
    }

    char buffer[96];

    snprintf(buffer, sizeof(buffer), "X: %.2f°", g_uiData.xAngle);
    lv_label_set_text(labelX, buffer);

    snprintf(buffer, sizeof(buffer), "Y: %.2f°", g_uiData.yAngle);
    lv_label_set_text(labelY, buffer);

    snprintf(
        buffer,
        sizeof(buffer),
        "WiFi:%s  USB:%s  BAT:%.0f%%",
        g_uiData.wifiConnected ? "ON" : "OFF",
        g_uiData.usbConnected ? "ON" : "OFF",
        g_uiData.batteryPercent
    );
    lv_label_set_text(labelStatusBar, buffer);

    lv_label_set_text(labelStatus, system_state_to_text(g_uiData.state));
    lv_obj_set_style_text_color(labelStatus, get_state_color(g_uiData.state), 0);
}