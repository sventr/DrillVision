#include <Arduino.h>
#include <Wire.h>

void i2c_scan()
{
    Serial.println();
    Serial.println("I2C Scan gestartet");

    for (uint8_t addr = 1; addr < 127; addr++)
    {
        Wire.beginTransmission(addr);

        if (Wire.endTransmission() == 0)
        {
            Serial.printf("I2C Device gefunden: 0x%02X\n", addr);
        }
    }

    Serial.println("I2C Scan beendet");
}