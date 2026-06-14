#include <Arduino.h>

#include "display_manager.h"
#include "config.h"
#include "system_state.h"
#include "lvgl_port.h"
#include "screen_manager.h"

static uint32_t lastSwitch = 0;

void display_init()
{
    Serial.println("Display Manager gestartet");
    Serial.println("Display Hardware noch nicht aktiv");

    lvgl_port_init();
    screen_manager_init();
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
    );

    lvgl_port_update();
    screen_manager_update();

    if (millis() - lastSwitch > 5000)
    {
        lastSwitch = millis();
        screen_manager_next();
    }
}