#include <Arduino.h>

#include "drillvision.h"
#include "config.h"
#include "sensor.h"

DrillVisionApp DrillVision;

void DrillVisionApp::begin()
{
    Serial.println();
    Serial.println("==============================");
    Serial.print(PROJECT_NAME);
    Serial.print(" ");
    Serial.println(PROJECT_VERSION);
    Serial.println("==============================");

    sensor_init();
}

void DrillVisionApp::update()
{
    sensor_update();

    Serial.printf(
        "X: %.2f°  Y: %.2f°\n",
        sensor_get_x(),
        sensor_get_y()
    );
}