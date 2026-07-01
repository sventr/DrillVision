#include <Arduino.h>
#include <lvgl.h>

#include "screen_boot.h"
#include "config.h"

static lv_obj_t* labelTitle = nullptr;
static lv_obj_t* labelVersion = nullptr;
static lv_obj_t* labelMessage = nullptr;
static lv_obj_t* barProgress = nullptr;
static lv_obj_t* labelPercent = nullptr;

void screen_boot_create()
{
    lv_obj_t* screen = lv_scr_act();
    lv_obj_clean(screen);

    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);

    labelTitle = lv_label_create(screen);
    lv_label_set_text(labelTitle, "DRILLVISION");
    lv_obj_set_style_text_color(labelTitle, lv_color_hex(0x00FF66), 0);
    lv_obj_align(labelTitle, LV_ALIGN_TOP_MID, 0, 80);

    labelVersion = lv_label_create(screen);
    lv_label_set_text(labelVersion, PROJECT_VERSION);
    lv_obj_set_style_text_color(labelVersion, lv_color_white(), 0);
    lv_obj_align(labelVersion, LV_ALIGN_TOP_MID, 0, 120);

    labelMessage = lv_label_create(screen);
    lv_label_set_text(labelMessage, "Initialisiere...");
    lv_obj_set_style_text_color(labelMessage, lv_color_white(), 0);
    lv_obj_align(labelMessage, LV_ALIGN_CENTER, 0, -10);

    barProgress = lv_bar_create(screen);
    lv_obj_set_size(barProgress, 260, 16);
    lv_obj_align(barProgress, LV_ALIGN_CENTER, 0, 50);
    lv_bar_set_range(barProgress, 0, 100);
    lv_bar_set_value(barProgress, 0, LV_ANIM_OFF);

    labelPercent = lv_label_create(screen);
    lv_label_set_text(labelPercent, "0%");
    lv_obj_set_style_text_color(labelPercent, lv_color_hex(0x00FF66), 0);
    lv_obj_align(labelPercent, LV_ALIGN_CENTER, 0, 85);
}

void screen_boot_update(int percent, const char* message)
{
    if (!labelMessage || !barProgress || !labelPercent)
    {
        return;
    }

    char buffer[16];

    lv_label_set_text(labelMessage, message);
    lv_bar_set_value(barProgress, percent, LV_ANIM_ON);

    snprintf(buffer, sizeof(buffer), "%d%%", percent);
    lv_label_set_text(labelPercent, buffer);

    lv_timer_handler();
}