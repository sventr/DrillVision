#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include "sensor.h"
#include "angle_math.h"
#include "config.h"
#include "qmi8658_driver.h"

static float xAngle = 0.0f;
static float yAngle = 0.0f;

static const uint8_t QMI8658_ADDR = 0x6B;

// QMI8658 output registers
static const uint8_t QMI8658_AX_L = 0x35;

static int16_t read_i16(uint8_t reg)
{
    Wire.beginTransmission(QMI8658_ADDR);
    Wire.write(reg);

    if (Wire.endTransmission(false) != 0)
    {
        return 0;
    }

    Wire.requestFrom(QMI8658_ADDR, (uint8_t)2);

    if (Wire.available() < 2)
    {
        return 0;
    }

    uint8_t l = Wire.read();
    uint8_t h = Wire.read();

    return (int16_t)((h << 8) | l);
}

static uint8_t write_register(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(QMI8658_ADDR);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission();
}

static void qmi8658_configure()
{
    // Enable accelerometer and gyroscope
    // This is a basic bringup configuration.
    write_register(0x02, 0x60); // Ctrl1
    write_register(0x03, 0x03); // Ctrl2 accelerometer range/odr placeholder
    write_register(0x04, 0x54); // Ctrl3 gyroscope placeholder
    write_register(0x08, 0x03); // Ctrl7 enable accel + gyro
}

void sensor_init()
{
#if ACTIVE_SENSOR_MODE == SENSOR_MODE_QMI8658

    Serial.println("Sensor Mode: QMI8658");

    if (qmi8658_init())
    {
        qmi8658_configure();
        Serial.println("QMI8658 Sensor initialisiert");
    }
    else
    {
        Serial.println("QMI8658 nicht verfügbar, Sensorwerte bleiben 0");
    }

#else

    Serial.println("Sensor Simulation gestartet");

#endif
}

void sensor_update()
{
#if ACTIVE_SENSOR_MODE == SENSOR_MODE_QMI8658

    int16_t rawAx = read_i16(QMI8658_AX_L + 0);
    int16_t rawAy = read_i16(QMI8658_AX_L + 2);
    int16_t rawAz = read_i16(QMI8658_AX_L + 4);

    // Temporary scaling for bringup.
    // Exact scale will be tuned after raw data validation.
    float ax = rawAx / 4096.0f;
    float ay = rawAy / 4096.0f;
    float az = rawAz / 4096.0f;

    AngleResult angle = calculate_angles(ax, ay, az);

    xAngle = angle.x;
    yAngle = angle.y;

#else

    static float sim = 0.0f;

    sim += 0.05f;

    float ax = sin(sim) * 0.2f;
    float ay = cos(sim) * 0.2f;
    float az = 1.0f;

    AngleResult angle = calculate_angles(ax, ay, az);

    xAngle = angle.x;
    yAngle = angle.y;

#endif
}

float sensor_get_x()
{
    return xAngle;
}

float sensor_get_y()
{
    return yAngle;
}