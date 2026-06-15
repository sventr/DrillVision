#pragma once

void battery_init();

float battery_get_percent();

float battery_get_voltage();

bool battery_is_charging();

bool battery_usb_connected();