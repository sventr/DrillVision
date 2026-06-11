# DrillVision UI Specification V4.1

## Display

- Resolution: 480 x 480 px
- Shape: round
- Background: black
- Primary color: neon green
- Warning color: yellow
- Alarm color: red
- Text color: white

## Main Screen

### Header

- Position: top center
- Project name: BOHRVISION
- Version: V4.1

### Status Bar

Position: upper third

Items:

- WiFi signal
- USB connection
- Battery level
- Charging status
- Temperature

### Center Crosshair

Position: center

Elements:

- horizontal axis
- vertical axis
- center circle
- tick marks
- moving center point

Purpose:

Shows deviation from target drilling alignment.

### Angle Values

Left side:

```text
X
+0.2°
ROLL

Bottom center:

Y
-0.3°
PITCH
Outer Ring

Purpose:

Visual indication of deviation.

Rules:

Deviation	Color	Meaning
0.0° - 0.3°	Green	In level
0.3° - 1.0°	Yellow	Warning
> 1.0°	Red	Out of level
Bottom Controls
Menu button
Calibration button
Precision display: 0.1° / DIV
Calibration State
Text: KALIBRIERT
Icon: green check mark
Only visible when calibration is valid
Screen States
Normal

Shows live X/Y angle values.

In Level

Condition:

abs(X) <= 0.3° and abs(Y) <= 0.3°

Status text:

IM LOT
Warning

Condition:

0.3° < deviation <= 1.0°

Status text:

KORRIGIEREN
Alarm

Condition:

deviation > 1.0°

Status text:

AUSSER LOT
Layout Coordinates

Display center:

X = 240
Y = 240

Main crosshair:

Center: 240 / 250
Horizontal line: x 115 - 365
Vertical line: y 160 - 350
Center circle: radius 42 px

Outer ring:

Center: 240 / 240
Radius: 210 px
Dot count: 72
Dot size: 8 px

Header:

Project title: x 240 / y 58
Version: x 240 / y 95

Status icons:

WiFi: x 90 / y 125
USB: x 165 / y 125
Battery: x 240 / y 125
Charge: x 315 / y 125
Temp: x 390 / y 125

Angle values:

X angle: x 90 / y 255
Y angle: x 240 / y 365

Buttons:

Menu: x 120 / y 400
Calibration: x 345 / y 400
Future Screens
Calibration screen
Settings screen
Battery screen
WiFi / OTA screen
Sensor diagnostics screen


```powershell
git add .
git commit -m "Add UI specification V4.1"
git push