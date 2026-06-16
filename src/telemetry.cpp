#include <Arduino.h>
#include <ArduinoJson.h>

#include "telemetry.h"
#include "ui_model.h"
#include "system_state.h"
#include "config.h"

static uint32_t lastSend = 0;

void telemetry_init()
{
}

void telemetry_send()
{
    if (millis() - lastSend < 100)
    {
        return;
    }

    lastSend = millis();

    StaticJsonDocument<256> doc;

    doc["device"] = PROJECT_NAME;
    doc["version"] = PROJECT_VERSION;

    doc["timestamp"] = millis();

    doc["roll"] = g_uiData.xAngle;
    doc["pitch"] = g_uiData.yAngle;

    doc["battery"] = g_uiData.batteryPercent;
    doc["temperature"] = g_uiData.temperatureC;

    doc["wifi"] = g_uiData.wifiConnected;
    doc["usb"] = g_uiData.usbConnected;
    doc["charging"] = g_uiData.charging;

    doc["state"] = system_state_to_text(g_uiData.state);

    serializeJson(doc, Serial);
    Serial.println();
}