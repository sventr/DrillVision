#pragma once

void battery_init();

float battery_get_percent();

bool battery_is_charging();

bool battery_usb_connected();