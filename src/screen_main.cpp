#include <Arduino.h>
#include <lvgl.h>
#include <math.h>

#include "screen_main.h"
#include "ui_model.h"
#include "system_state.h"
#include "config.h"
#include "sensor.h"
#include "calibration.h"

static lv_obj_t* labelTitle = nullptr;
static lv_obj_t* labelVersion = nullptr;
static lv_obj_t* labelStatusBar = nullptr;
static lv_obj_t* labelX = nullptr;
static lv_obj_t* labelY = nullptr;
static lv_obj_t* labelStatus = nullptr;
static lv_obj_t* labelCalibration = nullptr;
static lv_obj_t* labelPrecision = nullptr;
static lv_obj_t* buttonCalibrate = nullptr;
static lv_obj_t* labelCalibrationState = nullptr;

static lv_obj_t* lineHorizontal = nullptr;
static lv_obj_t* lineVertical = nullptr;
static lv_obj_t* centerCircle = nullptr;
static lv_obj_t* targetDot = nullptr;

static lv_obj_t* outerDots[72] = { nullptr };
static lv_obj_t* tickMarks[8] = { nullptr };

static constexpr float DEGREES_PER_DIV = 0.1f;
static constexpr float PIXELS_PER_DIV = 30.0f;

static float smoothBubbleX = 233.0f;
static float smoothBubbleY = 243.0f;

static lv_point_t horizontalPoints[] = {
    {115, 250},
    {365, 250}
};

static lv_point_t verticalPoints[] = {
    {240, 160},
    {240, 350}
};

static lv_point_t tickPoints[8][2] = {
    {{180, 240}, {180, 260}},
    {{210, 240}, {210, 260}},
    {{270, 240}, {270, 260}},
    {{300, 240}, {300, 260}},
    {{230, 190}, {250, 190}},
    {{230, 220}, {250, 220}},
    {{230, 280}, {250, 280}},
    {{230, 310}, {250, 310}}
};

static lv_color_t get_state_color(SystemState state)
{
    switch (state)
    {
        case SystemState::InLevel: return lv_color_hex(0x00FF66);
        case SystemState::Warning: return lv_color_hex(0xFFCC00);
        case SystemState::Alarm: return lv_color_hex(0xFF3300);
        default: return lv_color_hex(0xFFFFFF);
    }
}

static void create_outer_ring(lv_obj_t* screen)
{
    const int centerX = 240;
    const int centerY = 240;
    const int radius = 210;
    const int dotSize = 8;
    const int dotCount = 72;

    for (int i = 0; i < dotCount; i++)
    {
        float angle = (2.0f * PI * i) / dotCount;
        int x = centerX + (int)(cos(angle) * radius) - dotSize / 2;
        int y = centerY + (int)(sin(angle) * radius) - dotSize / 2;

        outerDots[i] = lv_obj_create(screen);
        lv_obj_set_size(outerDots[i], dotSize, dotSize);
        lv_obj_set_pos(outerDots[i], x, y);
        lv_obj_set_style_radius(outerDots[i], LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_border_width(outerDots[i], 0, 0);
        lv_obj_set_style_bg_color(outerDots[i], lv_color_hex(0x333333), 0);
    }
}

static void create_tick_marks(lv_obj_t* screen)
{
    for (int i = 0; i < 8; i++)
    {
        tickMarks[i] = lv_line_create(screen);
        lv_line_set_points(tickMarks[i], tickPoints[i], 2);
        lv_obj_set_style_line_color(tickMarks[i], lv_color_hex(0x00FF66), 0);
        lv_obj_set_style_line_width(tickMarks[i], 2, 0);
    }
}

static void calibrate_button_event_cb(lv_event_t* e)
{
    static uint32_t lastCalibrateMs = 0;

    if (millis() - lastCalibrateMs < 1500)
    {
        return;
    }

    lastCalibrateMs = millis();

    Serial.println("TOUCH KALIBRIERUNG");

    sensor_calibrate_zero();

    smoothBubbleX = 236;
    smoothBubbleY = 243.0f;

   if (targetDot)
{
    lv_obj_set_pos(targetDot, 233, 243);
}
    float pixelsPerDegree = PIXELS_PER_DIV / DEGREES_PER_DIV;

    float displayX = g_uiData.xAngle;
    float displayY = g_uiData.yAngle;

    const float uiDeadzone = 0.25f;

    if (fabs(displayX) < uiDeadzone) displayX = 0.0f;
    if (fabs(displayY) < uiDeadzone) displayY = 0.0f;

    int xOffset = (int)(displayY * pixelsPerDegree);
    int yOffset = (int)(displayX * pixelsPerDegree);

    if (xOffset > 80) xOffset = 80;
    if (xOffset < -80) xOffset = -80;
    if (yOffset > 80) yOffset = 80;
    if (yOffset < -80) yOffset = -80;

    float targetX = 233.0f + xOffset;
    float targetY = 243.0f + yOffset;

    const float alpha = 0.14f;

    smoothBubbleX = smoothBubbleX + alpha * (targetX - smoothBubbleX);
    smoothBubbleY = smoothBubbleY + alpha * (targetY - smoothBubbleY);

    lv_obj_set_pos(targetDot, (int)smoothBubbleX, (int)smoothBubbleY);
}


void screen_main_create()
{
    lv_obj_clean(lv_scr_act());

    Serial.println("Main Screen LVGL erstellt");

    lv_obj_t* screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_black(), 0);

    smoothBubbleX = 236;
    smoothBubbleY = 243.0f;

    create_outer_ring(screen);
    create_tick_marks(screen);

    labelTitle = lv_label_create(screen);
    lv_label_set_text(labelTitle, "DRILLVISION");
    lv_obj_set_style_text_color(labelTitle, lv_color_hex(0x00FF66), 0);
    lv_obj_align(labelTitle, LV_ALIGN_TOP_MID, 0, 35);

    labelVersion = lv_label_create(screen);
    lv_label_set_text(labelVersion, PROJECT_VERSION);
    lv_obj_set_style_text_color(labelVersion, lv_color_white(), 0);
    lv_obj_align(labelVersion, LV_ALIGN_TOP_MID, 0, 62);

    labelStatusBar = lv_label_create(screen);
    lv_label_set_text(labelStatusBar, "WiFi:OFF  USB:ON  BAT:100%  23.5C");
    lv_obj_set_style_text_color(labelStatusBar, lv_color_white(), 0);
    lv_obj_align(labelStatusBar, LV_ALIGN_TOP_MID, 0, 98);

    labelCalibration = lv_label_create(screen);
    lv_label_set_text(labelCalibration, "CAL");
    lv_obj_set_style_text_color(labelCalibration, lv_color_hex(0x00FF66), 0);
    lv_obj_align(labelCalibration, LV_ALIGN_TOP_RIGHT, -55, 125);

    labelPrecision = lv_label_create(screen);
    lv_label_set_text(labelPrecision, "0.1° / DIV");
    lv_obj_set_style_text_color(labelPrecision, lv_color_white(), 0);
    lv_obj_align(labelPrecision, LV_ALIGN_BOTTOM_MID, 0, -10);

    lineHorizontal = lv_line_create(screen);
    lv_line_set_points(lineHorizontal, horizontalPoints, 2);
    lv_obj_set_style_line_color(lineHorizontal, lv_color_hex(0x00FF66), 0);
    lv_obj_set_style_line_width(lineHorizontal, 3, 0);

    lineVertical = lv_line_create(screen);
    lv_line_set_points(lineVertical, verticalPoints, 2);
    lv_obj_set_style_line_color(lineVertical, lv_color_hex(0x00FF66), 0);
    lv_obj_set_style_line_width(lineVertical, 3, 0);

    centerCircle = lv_obj_create(screen);
    lv_obj_set_size(centerCircle, 84, 84);
    lv_obj_set_pos(centerCircle, 198, 208);
    lv_obj_set_style_radius(centerCircle, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_opa(centerCircle, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(centerCircle, 3, 0);
    lv_obj_set_style_border_color(centerCircle, lv_color_hex(0x00FF66), 0);

    targetDot = lv_obj_create(screen);
    lv_obj_set_size(targetDot, 14, 14);
    lv_obj_set_pos(targetDot, 233, 243);
    lv_obj_set_style_radius(targetDot, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_border_width(targetDot, 0, 0);
    lv_obj_set_style_bg_color(targetDot, lv_color_hex(0x00FF66), 0);

    labelX = lv_label_create(screen);
    lv_label_set_text(labelX, "X: 0.00°");
    lv_obj_set_style_text_color(labelX, lv_color_white(), 0);
    lv_obj_align(labelX, LV_ALIGN_LEFT_MID, 45, 0);

    labelY = lv_label_create(screen);
    lv_label_set_text(labelY, "Y: 0.00°");
    lv_obj_set_style_text_color(labelY, lv_color_white(), 0);
    lv_obj_align(labelY, LV_ALIGN_BOTTOM_MID, 0, -75);

    labelStatus = lv_label_create(screen);
    lv_label_set_text(labelStatus, "STARTUP");
    lv_obj_set_style_text_color(labelStatus, lv_color_white(), 0);
    lv_obj_align(labelStatus, LV_ALIGN_BOTTOM_MID, 0, -35);

    buttonCalibrate = lv_btn_create(screen);
    lv_obj_clear_flag(buttonCalibrate, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(buttonCalibrate, 170, 42);
    lv_obj_align(buttonCalibrate, LV_ALIGN_BOTTOM_MID, 0, -18);
    lv_obj_set_style_bg_color(buttonCalibrate, lv_color_hex(0x404040), LV_PART_MAIN);
lv_obj_add_event_cb(buttonCalibrate, calibrate_button_event_cb, LV_EVENT_RELEASED, NULL);

    lv_obj_t* label = lv_label_create(buttonCalibrate);
    lv_label_set_text(label, "KALIBRIEREN");
    lv_obj_center(label);

    labelCalibrationState = lv_label_create(screen);
    lv_label_set_text(labelCalibrationState, "NICHT KALIBRIERT");
    lv_obj_set_style_text_color(labelCalibrationState, lv_color_hex(0xFF4444), 0);
    lv_obj_align(labelCalibrationState, LV_ALIGN_BOTTOM_MID, 0, -68);
}

void screen_main_update()
{
    if (!labelX || !labelY || !labelStatusBar || !labelStatus ||
        !labelCalibration || !labelPrecision)
    {
        return;
    }

    char buffer[96];

    static int lastX20 = 99999;
    static int lastY20 = 99999;
    static int lastBattery = -1;
    static int lastTemp10 = -9999;
    static bool lastWifi = false;
    static bool lastUsb = false;
    static bool firstStatusBar = true;
    static SystemState lastState = (SystemState)-1;
    static bool lastCalibrated = false;
    static bool firstCalState = true;
    static int lastActiveDots = -1;
    static int lastBubbleX = 233;
    static int lastBubbleY = 243;

    int x20 = (int)(g_uiData.xAngle * 20.0f);  // 0.05°
    int y20 = (int)(g_uiData.yAngle * 20.0f);  // 0.05°

    if (x20 != lastX20)
    {
        lastX20 = x20;
        snprintf(buffer, sizeof(buffer), "X: %.2f°", g_uiData.xAngle);
        lv_label_set_text(labelX, buffer);
    }

    if (y20 != lastY20)
    {
        lastY20 = y20;
        snprintf(buffer, sizeof(buffer), "Y: %.2f°", g_uiData.yAngle);
        lv_label_set_text(labelY, buffer);
    }

    int batteryInt = (int)g_uiData.batteryPercent;
    int temp10 = (int)(g_uiData.temperatureC * 10.0f);

    if (firstStatusBar ||
        batteryInt != lastBattery ||
        temp10 != lastTemp10 ||
        g_uiData.wifiConnected != lastWifi ||
        g_uiData.usbConnected != lastUsb)
    {
        firstStatusBar = false;
        lastBattery = batteryInt;
        lastTemp10 = temp10;
        lastWifi = g_uiData.wifiConnected;
        lastUsb = g_uiData.usbConnected;

        snprintf(
            buffer,
            sizeof(buffer),
            "WiFi:%s  USB:%s  BAT:%d%%  %.1fC",
            g_uiData.wifiConnected ? "ON" : "OFF",
            g_uiData.usbConnected ? "ON" : "OFF",
            batteryInt,
            g_uiData.temperatureC
        );

        lv_label_set_text(labelStatusBar, buffer);
    }

    if (g_uiData.state != lastState)
    {
        lastState = g_uiData.state;

        lv_label_set_text(labelStatus, system_state_to_text(g_uiData.state));

        lv_color_t stateColor = get_state_color(g_uiData.state);

        lv_obj_set_style_text_color(labelStatus, stateColor, 0);
        lv_obj_set_style_text_color(labelCalibration, stateColor, 0);
    }

    bool calibrated = calibration_is_calibrated();

    if (firstCalState || calibrated != lastCalibrated)
    {
        firstCalState = false;
        lastCalibrated = calibrated;

        if (calibrated)
        {
            lv_label_set_text(labelCalibrationState, "KALIBRIERT");
            lv_obj_set_style_text_color(labelCalibrationState, lv_color_hex(0x00FF66), 0);
        }
        else
        {
            lv_label_set_text(labelCalibrationState, "NICHT KALIBRIERT");
            lv_obj_set_style_text_color(labelCalibrationState, lv_color_hex(0xFF4444), 0);
        }
    }

    float displayX = g_uiData.xAngle;
    float displayY = g_uiData.yAngle;

    const float uiDeadzone = 0.35f;

    if (fabs(displayX) < uiDeadzone) displayX = 0.0f;
    if (fabs(displayY) < uiDeadzone) displayY = 0.0f;

    float deviation = fmax(fabs(displayX), fabs(displayY));

    int activeDots = (int)(deviation * 24.0f);
    if (activeDots < 1) activeDots = 1;
    if (activeDots > 72) activeDots = 72;

    if (activeDots != lastActiveDots)
    {
        lastActiveDots = activeDots;

        lv_color_t ringColor = get_state_color(g_uiData.state);

        for (int i = 0; i < 72; i++)
        {
            if (!outerDots[i]) continue;

            lv_obj_set_style_bg_color(
                outerDots[i],
                i < activeDots ? ringColor : lv_color_hex(0x333333),
                0
            );
        }
    }

    if (targetDot)if (targetDot)
{
    float pixelsPerDegree = PIXELS_PER_DIV / DEGREES_PER_DIV;

    float displayX = g_uiData.xAngle;
    float displayY = g_uiData.yAngle;

    const float uiDeadzone = 0.35f;

    if (fabs(displayX) < uiDeadzone) displayX = 0.0f;
    if (fabs(displayY) < uiDeadzone) displayY = 0.0f;

    int xOffset = (int)(displayY * pixelsPerDegree);
    int yOffset = (int)(displayX * pixelsPerDegree);

    if (xOffset > 80) xOffset = 80;
    if (xOffset < -80) xOffset = -80;
    if (yOffset > 80) yOffset = 80;
    if (yOffset < -80) yOffset = -80;

    float targetX = 233.0f + xOffset;
    float targetY = 243.0f + yOffset;

    const float alpha = 0.14f;

    smoothBubbleX = smoothBubbleX + alpha * (targetX - smoothBubbleX);
    smoothBubbleY = smoothBubbleY + alpha * (targetY - smoothBubbleY);

    lv_obj_set_pos(targetDot, (int)smoothBubbleX, (int)smoothBubbleY);
}
    {
  

        int newX = (int)(smoothBubbleX + 0.5f);
        int newY = (int)(smoothBubbleY + 0.5f);

        if (newX != lastBubbleX || newY != lastBubbleY)
        {
            lastBubbleX = newX;
            lastBubbleY = newY;

            lv_obj_set_pos(targetDot, newX, newY);
        }
    }
}