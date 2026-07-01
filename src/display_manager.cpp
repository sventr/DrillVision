#include <Arduino.h>
#include <lvgl.h>

#include "display_manager.h"
#include "Display_ST7701.h"
#include "LVGL_Driver.h"
#include "screen_main.h"
#include "screen_boot.h"

void display_init()
{
    Serial.println("Display Manager gestartet");

    LCD_Init();
    Lvgl_Init();

    screen_boot_create();

    screen_boot_update(20, "Display OK");
    delay(400);

    screen_boot_update(45, "Sensor bereit");
    delay(400);

    screen_boot_update(70, "Kalibrierung bereit");
    delay(400);

    screen_boot_update(100, "System bereit");
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