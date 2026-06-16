#pragma once

#include <Arduino.h>

bool qmi8658_init();

bool qmi8658_is_available();

uint8_t qmi8658_read_chip_id();