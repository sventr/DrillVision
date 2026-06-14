#include <Arduino.h>
#include <lvgl.h>

#include "screen_calibration.h"
#include "calibration.h"
#include "config.h"

static lv_obj_t* labelTitle = nullptr;
static lv_obj_t* labelXOffset = nullptr;
static lv_obj_t* labelYOffset = nullptr;
static lv_obj_t* labelInfo = nullptr;

void screen_calibration_create()
{
    Serial.println("Calibration Screen erstellt");

    lv_obj_t* screen = lv_scr_act();

    labelTitle = lv_label_create(screen);
    lv_label_set_text(labelTitle, "CALIBRATION");
    lv_obj_align(labelTitle, LV_ALIGN_TOP_MID, 0, 40);

    labelInfo = lv_label_create(screen);
    lv_label_set_text(
        labelInfo,
        "Place drill vertically\nand press SAVE"
    );
    lv_obj_align(labelInfo, LV_ALIGN_TOP_MID, 0, 100);

    labelXOffset = lv_label_create(screen);
    lv_label_set_text(labelXOffset, "X Offset: 0.00");
    lv_obj_align(labelXOffset, LV_ALIGN_CENTER, 0, -25);

    labelYOffset = lv_label_create(screen);
    lv_label_set_text(labelYOffset, "Y Offset: 0.00");
    lv_obj_align(labelYOffset, LV_ALIGN_CENTER, 0, 5);

    lv_obj_t* saveButton = lv_btn_create(screen);
    lv_obj_set_size(saveButton, 140, 50);
    lv_obj_align(saveButton, LV_ALIGN_CENTER, 0, 60);

    lv_obj_t* saveLabel = lv_label_create(saveButton);
    lv_label_set_text(saveLabel, "SAVE");
    lv_obj_center(saveLabel);

    lv_obj_t* resetButton = lv_btn_create(screen);
    lv_obj_set_size(resetButton, 140, 50);
    lv_obj_align(resetButton, LV_ALIGN_CENTER, 0, 125);

    lv_obj_t* resetLabel = lv_label_create(resetButton);
    lv_label_set_text(resetLabel, "RESET");
    lv_obj_center(resetLabel);
}

void screen_calibration_update()
{
    if (!labelXOffset || !labelYOffset)
    {
        return;
    }

    char buffer[64];

    snprintf(
        buffer,
        sizeof(buffer),
        "X Offset: %.2f",
        calibration_get_x_offset()
    );
    lv_label_set_text(labelXOffset, buffer);

    snprintf(
        buffer,
        sizeof(buffer),
        "Y Offset: %.2f",
        calibration_get_y_offset()
    );
    lv_label_set_text(labelYOffset, buffer);
}