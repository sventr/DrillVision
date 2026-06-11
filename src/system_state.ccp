#include <math.h>
#include "system_state.h"

SystemState system_state_from_angles(float xAngle, float yAngle)
{
    float maxDeviation = fmax(fabs(xAngle), fabs(yAngle));

    if (maxDeviation <= 0.3f)
    {
        return SystemState::InLevel;
    }

    if (maxDeviation <= 1.0f)
    {
        return SystemState::Warning;
    }

    return SystemState::Alarm;
}

const char* system_state_to_text(SystemState state)
{
    switch (state)
    {
        case SystemState::Startup:
            return "STARTUP";
        case SystemState::Normal:
            return "NORMAL";
        case SystemState::InLevel:
            return "IM LOT";
        case SystemState::Warning:
            return "KORRIGIEREN";
        case SystemState::Alarm:
            return "AUSSER LOT";
        case SystemState::Calibrating:
            return "KALIBRIERUNG";
        case SystemState::Menu:
            return "MENU";
        default:
            return "UNKNOWN";
    }
}