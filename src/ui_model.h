#pragma once

#include "system_state.h"

struct UiData
{
    float xAngle;
    float yAngle;

    float batteryPercent;

    bool wifiConnected;
    bool usbConnected;
    bool charging;

    SystemState state;
};

extern UiData g_uiData;