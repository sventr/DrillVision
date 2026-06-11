#include <Arduino.h>

#include "ui_main.h"
#include "sensor.h"

void ui_init()
{
    Serial.println("UI gestartet");

    sensor_init();
}

void ui_update_fake_values()
{
    sensor_update();

    Serial.printf(
        "X: %.2f°  Y: %.2f°\n",
        sensor_get_x(),
        sensor_get_y()
    );
}