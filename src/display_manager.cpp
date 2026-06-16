#include <Arduino.h>
#include <lvgl.h>

#include "display_manager.h"
#include "Display_ST7701.h"
#include "LVGL_Driver.h"
#include "screen_main.h"

void display_init()
{
    Serial.println("Display Manager gestartet");

    LCD_Init();
    Lvgl_Init();

    screen_main_create();

    Serial.println("DrillVision Main UI gestartet");
}

void display_update(float xAngle, float yAngle, SystemState state)
{
    static uint32_t lastUi = 0;

    if (millis() - lastUi >= 33)
    {
        lastUi = millis();
        screen_main_update();
    }

    lv_timer_handler();
}