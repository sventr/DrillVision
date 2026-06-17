#pragma once

void sensor_init();
void sensor_update();

float sensor_get_x();
float sensor_get_y();
void sensor_reset_filter();