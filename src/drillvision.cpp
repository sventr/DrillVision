#include <Arduino.h>

#include "drillvision.h"
#include "config.h"
#include "sensor.h"
#include "display_manager.h"

DrillVisionApp DrillVision;

void DrillVisionApp::begin()
{
    Serial.println();
    Serial.println("=================================");
    Serial.print(PROJECT_NAME);
    Serial.print(" ");
    Serial.println(PROJECT_VERSION);
    Serial.println("=================================");

    sensor_init();
    display_init();
}

void DrillVisionApp::update()
{
    sensor_update();

    display_update(
        sensor_get_x(),
        sensor_get_y()
    );
}