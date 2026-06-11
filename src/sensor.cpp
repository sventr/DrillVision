#include <Arduino.h>
#include <math.h>

#include "sensor.h"
#include "angle_math.h"

static float xAngle = 0.0f;
static float yAngle = 0.0f;

void sensor_init()
{
    Serial.println("Sensor Simulation gestartet");
}

void sensor_update()
{
    static float sim = 0.0f;

    sim += 0.05f;

    float ax = sin(sim) * 0.2f;
    float ay = cos(sim) * 0.2f;
    float az = 1.0f;

    AngleResult angle = calculate_angles(ax, ay, az);

    xAngle = angle.x;
    yAngle = angle.y;
}

float sensor_get_x()
{
    return xAngle;
}

float sensor_get_y()
{
    return yAngle;
}