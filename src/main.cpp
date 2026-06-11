#include <Arduino.h>
#include "drillvision.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);

    DrillVision.begin();
}

void loop()
{
    DrillVision.update();
    delay(100);
}