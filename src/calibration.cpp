#include "calibration.h"

static float g_xOffset = 0.0f;
static float g_yOffset = 0.0f;

void calibration_init()
{
    g_xOffset = 0.0f;
    g_yOffset = 0.0f;
}

float calibration_apply_x(float rawX)
{
    return rawX - g_xOffset;
}

float calibration_apply_y(float rawY)
{
    return rawY - g_yOffset;
}

void calibration_set_offset(float xOffset, float yOffset)
{
    g_xOffset = xOffset;
    g_yOffset = yOffset;
}

float calibration_get_x_offset()
{
    return g_xOffset;
}

float calibration_get_y_offset()
{
    return g_yOffset;
}
void calibration_set_zero(float currentX, float currentY)
{
    calibration_set_offset(
        currentX + calibration_get_x_offset(),
        currentY + calibration_get_y_offset()
    );
}