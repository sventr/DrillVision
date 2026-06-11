#include <Arduino.h>
#include "ui_main.h"

void setup()
{
    Serial.begin(115200);

    ui_init();
}

void loop()
{
    ui_update_fake_values();

    delay(100);
}