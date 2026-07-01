#include <Arduino.h>
#include <lvgl.h>
#include <string.h>

#include "screen_boot.h"
#include "config.h"
#include "assets/drillvision_boot_logo.h"

static lv_obj_t* imgLogo = nullptr;
static lv_obj_t* labelCopyright = nullptr;

static lv_obj_t* labelTitle = nullptr;
static lv_obj_t* labelMessage = nullptr;
static lv_obj_t* labelDisplay = nullptr;
static lv_obj_t* labelSensor = nullptr;
static lv_obj_t* labelStorage = nullptr;
static lv_obj_t* labelSystem = nullptr;
static lv_obj_t* barProgress = nullptr;
static lv_obj_t* labelPercent = nullptr;

static void setStatus(lv_obj_t* obj, const char* text, bool ok)
{
    if (!obj) return;

    lv_label_set_text(obj, text);
    lv_obj_set_style_text_color(
        obj,
        ok ? lv_color_hex(0x39D353) : lv_color_hex(0x707070),
        0
    );
}

void screen_boot_create()
{
    lv_obj_t* screen = lv_scr_act();
    lv_obj_clean(screen);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);

    imgLogo = lv_img_create(screen);
    lv_img_set_src(imgLogo, &drillvision_boot_logo);
    lv_obj_align(imgLogo, LV_ALIGN_CENTER, 0, -20);

    labelCopyright = lv_label_create(screen);
    lv_label_set_text(labelCopyright, "© 2025–2027 Sven Treese");
    lv_obj_set_style_text_color(labelCopyright, lv_color_hex(0x909090), 0);
    lv_obj_align(labelCopyright, LV_ALIGN_BOTTOM_MID, 0, -18);

    lv_timer_handler();
}

void screen_boot_show_test()
{
    lv_obj_t* screen = lv_scr_act();
    lv_obj_clean(screen);
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);

    labelTitle = lv_label_create(screen);
    lv_label_set_text(labelTitle, "DRILLVISION");
    lv_obj_set_style_text_color(labelTitle, lv_color_hex(0x39D353), 0);
    lv_obj_align(labelTitle, LV_ALIGN_TOP_MID, 0, 45);

    labelMessage = lv_label_create(screen);
    lv_label_set_text(labelMessage, "Initializing Hardware...");
    lv_obj_set_style_text_color(labelMessage, lv_color_white(), 0);
    lv_obj_align(labelMessage, LV_ALIGN_TOP_MID, 0, 82);

    labelDisplay = lv_label_create(screen);
    lv_obj_align(labelDisplay, LV_ALIGN_CENTER, 0, -45);
    setStatus(labelDisplay, "○ Display", false);

    labelSensor = lv_label_create(screen);
    lv_obj_align(labelSensor, LV_ALIGN_CENTER, 0, -15);
    setStatus(labelSensor, "○ Sensor", false);

    labelStorage = lv_label_create(screen);
    lv_obj_align(labelStorage, LV_ALIGN_CENTER, 0, 15);
    setStatus(labelStorage, "○ Memory", false);

    labelSystem = lv_label_create(screen);
    lv_obj_align(labelSystem, LV_ALIGN_CENTER, 0, 45);
    setStatus(labelSystem, "○ System", false);

    barProgress = lv_bar_create(screen);
    lv_obj_set_size(barProgress, 300, 16);
    lv_obj_align(barProgress, LV_ALIGN_BOTTOM_MID, 0, -58);
    lv_bar_set_range(barProgress, 0, 100);
    lv_bar_set_value(barProgress, 0, LV_ANIM_OFF);

    labelPercent = lv_label_create(screen);
    lv_label_set_text(labelPercent, "0%");
    lv_obj_set_style_text_color(labelPercent, lv_color_hex(0x39D353), 0);
    lv_obj_align(labelPercent, LV_ALIGN_BOTTOM_MID, 0, -32);

    labelCopyright = lv_label_create(screen);
    lv_label_set_text(labelCopyright, "© 2025–2027 Sven Treese");
    lv_obj_set_style_text_color(labelCopyright, lv_color_hex(0x909090), 0);
    lv_obj_align(labelCopyright, LV_ALIGN_BOTTOM_MID, 0, -8);

    lv_timer_handler();
}

void screen_boot_update(int percent, const char* message)
{
    if (!barProgress || !labelPercent) return;

    if (message)
    {
        if (strcmp(message, "Display") == 0)
        {
            setStatus(labelDisplay, "✓ Display", true);
        }
        else if (strcmp(message, "Sensor") == 0)
        {
            setStatus(labelSensor, "✓ Sensor", true);
        }
        else if (strcmp(message, "Speicher") == 0 || strcmp(message, "Memory") == 0)
        {
            setStatus(labelStorage, "✓ Memory", true);
        }
        else if (strcmp(message, "System") == 0)
        {
            setStatus(labelSystem, "✓ System", true);

            if (labelMessage)
            {
                lv_label_set_text(labelMessage, "System Ready");
            }
        }
    }

    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;

    lv_bar_set_value(barProgress, percent, LV_ANIM_OFF);

    char txt[16];
    snprintf(txt, sizeof(txt), "%d%%", percent);
    lv_label_set_text(labelPercent, txt);

    lv_timer_handler();
}