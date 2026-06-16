#include <Arduino.h>

#include "waveshare_display.h"

static const int LCD_BACKLIGHT_PIN = 6;

void waveshare_display_init()
{
    Serial.println("Waveshare Display Init");

    pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
    digitalWrite(LCD_BACKLIGHT_PIN, HIGH);

    Serial.println("Backlight ON");
}

void waveshare_display_test()
{
}