#include <Arduino.h>
#include <lvgl.h>

#include "display_manager.h"
#include "Display_ST7701.h"
#include "LVGL_Driver.h"

#include "config.h"
#include "system_state.h"

void display_init()
{
    Serial.println("Display Manager gestartet");

    LCD_Init();

    Lvgl_Init();

    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "DRILLVISION");
    lv_obj_center(label);

    Serial.println("Display + LVGL fertig");
}

void display_update(float xAngle, float yAngle, SystemState state)
{
    lv_timer_handler();

    Serial.printf(
        "[DISPLAY] %s %s | X: %.2f | Y: %.2f | STATUS: %s\n",
        PROJECT_NAME,
        PROJECT_VERSION,
        xAngle,
        yAngle,
        system_state_to_text(state)
    );
}