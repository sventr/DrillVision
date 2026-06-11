#include <Arduino.h>

#include "display_manager.h"
#include "config.h"

void display_init()
{
    Serial.println("=================================");
    Serial.println("Display Manager gestartet");
    Serial.println("Display Hardware noch nicht aktiv");
    Serial.println("=================================");
}

void display_update(float xAngle, float yAngle)
{
    Serial.printf(
        "[DISPLAY] %s %s | X: %.2f° | Y: %.2f°\n",
        PROJECT_NAME,
        PROJECT_VERSION,
        xAngle,
        yAngle
    );
}