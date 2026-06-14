#include <Arduino.h>

#include "screen_main.h"
#include "ui_model.h"
#include "system_state.h"

void screen_main_create()
{
    Serial.println("=================================");
    Serial.println(" BOHRVISION V4.1");
    Serial.println(" Main Screen erstellt");
    Serial.println("=================================");
}

void screen_main_update()
{
    Serial.println();

    Serial.println("----------- UI -----------");

    Serial.printf(
        "X: %.2f°\n",
        g_uiData.xAngle
    );

    Serial.printf(
        "Y: %.2f°\n",
        g_uiData.yAngle
    );

    Serial.printf(
        "BAT: %.0f%%\n",
        g_uiData.batteryPercent
    );

    Serial.printf(
        "STATUS: %s\n",
        system_state_to_text(g_uiData.state)
    );

    Serial.println("--------------------------");
}