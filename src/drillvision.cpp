#include <Arduino.h>

#include "drillvision.h"
#include "config.h"
#include "sensor.h"
#include "display_manager.h"
#include "system_state.h"
#include "calibration.h"
#include "ui_model.h"
#include "battery_manager.h"
#include "telemetry.h"

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
    calibration_init();
    battery_init();
    telemetry_init();
    display_init();
}

void DrillVisionApp::update()
{
    sensor_update();

    float rawX = sensor_get_x();
    float rawY = sensor_get_y();

    float x = calibration_apply_x(rawX);
    float y = calibration_apply_y(rawY);

    SystemState state = system_state_from_angles(x, y);

    g_uiData.xAngle = x;
    g_uiData.yAngle = y;
    g_uiData.state = state;

    g_uiData.batteryPercent = battery_get_percent();
    g_uiData.charging = battery_is_charging();
    g_uiData.usbConnected = battery_usb_connected();

    display_update(x, y, state);

    telemetry_send();
}