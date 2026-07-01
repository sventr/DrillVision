#include <Arduino.h>
#include <lvgl.h>

#include "display_manager.h"
#include "Display_ST7701.h"
#include "LVGL_Driver.h"
#include "screen_boot.h"
#include "screen_main.h"

void display_init()
{
    Serial.println("Display Manager gestartet");

    LCD_Init();
    Lvgl_Init();

    screen_boot_create();

    for (int i = 0; i < 100; i++)
    {
        lv_timer_handler();
        delay(20);
    }

    screen_boot_show_test();

    screen_boot_update(25, "Display");
    delay(300);

    screen_boot_update(50, "Sensor");
    delay(300);

    screen_boot_update(75, "Memory");
    delay(300);

    screen_boot_update(100, "System");
    delay(600);

    screen_main_create();

    Serial.println("DrillVision Main UI gestartet");
}

void display_update(float xAngle, float yAngle, SystemState state)
{
    static uint32_t lastUi = 0;

    if (millis() - lastUi >= 50)
    {
        lastUi = millis();
        screen_main_update();
    }

    lv_timer_handler();
}