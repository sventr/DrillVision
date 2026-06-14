#include <Arduino.h>

#include "display_manager.h"
#include "config.h"
#include "system_state.h"
#include "lvgl_port.h"

void display_init()
{
    Serial.println("Display Manager gestartet");
    Serial.println("Display Hardware noch nicht aktiv");
    lvgl_port_init();
}

void display_update(float xAngle, float yAngle, SystemState state)
{
    Serial.printf(
        "[DISPLAY] %s %s | X: %.2f° | Y: %.2f° | STATUS: %s\n",
        PROJECT_NAME,
        PROJECT_VERSION,
        xAngle,
        yAngle,
        system_state_to_text(state)
        lvgl_port_update();
    );
}