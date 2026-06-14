#include <Arduino.h>

#include "drillvision.h"
#include "config.h"
#include "sensor.h"
#include "display_manager.h"
#include "system_state.h"
#include "calibration.h"

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
    calibration_init();
}

void DrillVisionApp::update()
{
    sensor_update();

    float rawX = sensor_get_x();
    float rawY = sensor_get_y();

    float x = calibration_apply_x(rawX);
    float y = calibration_apply_y(rawY);

    SystemState state = system_state_from_angles(x, y);

    display_update(x, y, state);
}
