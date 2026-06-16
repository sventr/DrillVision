#include <Arduino.h>
#include <Wire.h>

#include "qmi8658_driver.h"

static const uint8_t QMI8658_ADDR = 0x6B;
static bool qmiAvailable = false;

static uint8_t read_register(uint8_t reg)
{
    Wire.beginTransmission(QMI8658_ADDR);
    Wire.write(reg);

    if (Wire.endTransmission(false) != 0)
    {
        return 0xFF;
    }

    Wire.requestFrom(QMI8658_ADDR, (uint8_t)1);

    if (Wire.available())
    {
        return Wire.read();
    }

    return 0xFF;
}

bool qmi8658_init()
{
    uint8_t chipId = qmi8658_read_chip_id();

    Serial.printf("QMI8658 Chip ID: 0x%02X\n", chipId);

    qmiAvailable = (chipId != 0xFF && chipId != 0x00);

    if (qmiAvailable)
    {
        Serial.println("QMI8658 erkannt");
    }
    else
    {
        Serial.println("QMI8658 NICHT erkannt");
    }

    return qmiAvailable;
}

bool qmi8658_is_available()
{
    return qmiAvailable;
}

uint8_t qmi8658_read_chip_id()
{
    return read_register(0x00);
}