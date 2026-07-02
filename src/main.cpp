#include <Arduino.h>
#include <Wire.h>

#include "drillvision.h"
#include "i2c_scanner.h"
#include "qmi8658_driver.h"
#include "sensor.h"
#include "calibration.h"

void setup()
{
    Serial.begin(115200);
    delay(50);

    Serial.println("HELLO WAVESHARE");

    Wire.begin(15, 7);
    i2c_scan();
    qmi8658_init();

    calibration_init();

    DrillVision.begin();
}

void loop()
{
    DrillVision.update();

    if (Serial.available())
    {
        char c = Serial.read();

        if (c == 'z' || c == 'Z')
        {
            sensor_calibrate_zero();

            Serial.println("=================================");
            Serial.println("     SENSOR KALIBRIERT");
            Serial.println("=================================");
        }
    }

    delay(100);
}