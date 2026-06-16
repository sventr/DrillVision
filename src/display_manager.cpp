#include <Arduino.h>

#include "display_manager.h"
#include "Display_ST7701.h"

#include "config.h"
#include "system_state.h"
#include "esp_heap_caps.h"

static uint16_t* fullFrame = nullptr;

static void display_fill_color(uint16_t color)
{
    if (!fullFrame)
    {
        fullFrame = (uint16_t*)heap_caps_malloc(
            480 * 480 * sizeof(uint16_t),
            MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT
        );

        Serial.printf("fullFrame ptr: %p\n", fullFrame);
    }

    if (!fullFrame)
    {
        Serial.println("fullFrame allocation failed");
        return;
    }

    for (int i = 0; i < 480 * 480; i++)
    {
        fullFrame[i] = color;
    }

    LCD_addWindow(
        0,
        0,
        479,
        479,
        (uint8_t*)fullFrame
    );
}

void display_init()
{
    Serial.println("Display Manager gestartet");

    Serial.println("Vor LCD_Init");

    LCD_Init();

    Serial.println("Nach LCD_Init");

    delay(500);

    Serial.println("Display ROT Test startet");

    display_fill_color(0xF800);

    Serial.println("Display ROT Test fertig");
}

void display_update(float xAngle, float yAngle, SystemState state)
{
    Serial.printf(
        "[DISPLAY] %s %s | X: %.2f | Y: %.2f | STATUS: %s\n",
        PROJECT_NAME,
        PROJECT_VERSION,
        xAngle,
        yAngle,
        system_state_to_text(state)
    );
}