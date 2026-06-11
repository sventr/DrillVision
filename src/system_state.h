#pragma once

enum class SystemState
{
    Startup,
    Normal,
    InLevel,
    Warning,
    Alarm,
    Calibrating,
    Menu
};

SystemState system_state_from_angles(float xAngle, float yAngle);
const char* system_state_to_text(SystemState state);