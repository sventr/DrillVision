#pragma once

void wifi_init();

bool wifi_is_connected();

const char* wifi_get_ssid();

const char* wifi_get_ip();

bool wifi_ota_available();