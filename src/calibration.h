#pragma once

void calibration_init();

float calibration_apply_x(float rawX);
float calibration_apply_y(float rawY);

void calibration_set_offset(float xOffset, float yOffset);

float calibration_get_x_offset();
float calibration_get_y_offset();