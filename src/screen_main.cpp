#include <Arduino.h>
#include "screen_main.h"
#include "ui_model.h"

void screen_main_create()
{
    Serial.println("Main Screen erstellt");
}

void screen_main_update()
{
    Serial.printf(
        "[UI] X=%.2f  Y=%.2f  BAT=%.0f%%\n",
        g_uiData.xAngle,
        g_uiData.yAngle,
        g_uiData.batteryPercent
    );
}