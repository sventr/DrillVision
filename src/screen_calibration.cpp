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
}

void screen_calibration_update()
{
    Serial.printf(
        "[CAL] X Offset: %.2f | Y Offset: %.2f\n",
        calibration_get_x_offset(),
        calibration_get_y_offset()
    );
}