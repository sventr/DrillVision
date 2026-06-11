#include <Arduino.h>
#include <math.h>
#include "angle_math.h"

AngleResult calculate_angles(float ax, float ay, float az)
{
    AngleResult result;

    result.x = atan2(ax, sqrt(ay * ay + az * az)) * 180.0f / PI;
    result.y = atan2(ay, sqrt(ax * ax + az * az)) * 180.0f / PI;

    return result;
}