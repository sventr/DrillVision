#include <Arduino.h>
#include "display_manager.h"
#include "Display_ST7701.h"
#include "esp_heap_caps.h"

static uint16_t* fullFrame = nullptr;

void display_init()
{
    Serial.println("Display Manager gestartet");

    LCD_Init();

    fullFrame = (uint16_t*)heap_caps_malloc(
        480 * 480 * sizeof(uint16_t),
        MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT
    );

    Serial.printf("fullFrame ptr: %p\n", fullFrame);

    for (int i = 0; i < 480 * 480; i++)
    {
        fullFrame[i] = 0xF800;
    }

    LCD_addWindow(0, 0, 479, 479, (uint8_t*)fullFrame);

    Serial.println("Display ROT Test fertig");
}

void display_update(float xAngle, float yAngle, SystemState state)
{
}