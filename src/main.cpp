#include <Arduino.h>
#include "drillvision.h"

void setup()
{
    Serial.begin(115200);
   delay(3000);
Serial.println("HELLO WAVESHARE");
    DrillVision.begin();
}

void loop()
{
    DrillVision.update();
    delay(100);
}