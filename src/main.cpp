#include <Arduino.h>
#include <Wire.h>

#include "drillvision.h"
#include "i2c_scanner.h"
#include "qmi8658_driver.h"

void setup()
{
    Serial.begin(115200);
    delay(3000);

    Serial.println("HELLO WAVESHARE");

    Wire.begin(15, 7);
    i2c_scan();
    qmi8658_init();

    DrillVision.begin();
}

void loop()
{
    DrillVision.update();
    delay(100);
}