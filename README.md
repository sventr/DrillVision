# DrillVision V4.01

Digitale Bohrhilfe zur Ausrichtung einer Bohrmaschine für vertikales und horizontales Bohren.

## Ziel

DrillVision zeigt die Neigung der Bohrmaschine in X- und Y-Richtung an und hilft dabei, präzise im Lot oder waagerecht zu bohren.

## Hardware

- Waveshare ESP32-S3 Round Display
- QMI8658
- 1000 mAh LiPo-Akku
- Aluminiumgehäuse mit USB-C-Ladeausschnitt

## Status

- Projektstruktur erstellt
- GitHub eingerichtet
- Sensordaten-Simulation läuft
- Winkelberechnung vorbereitet
- Display-UI in Planung

## Screenshots

![UI Screenshot](docs/images/screenshot%20v4.1.png)

![Assembly](docs/images/assembly%20v2.1.png)

## Roadmap

- BMI270 anbinden
- Displaytreiber für Waveshare ESP32-S3 Round Display einrichten
- Fadenkreuz-UI erstellen
- Akkuanzeige integrieren
- Kalibrierung speichern

docs/architecture.md
docs/telemetry.md
docs/hardware.md

Controller
- Waveshare ESP32-S3 Round Display

MCU
- ESP32-S3

Display
- 480x480 Round LCD

IMU
- QMI8658

Software
- Arduino
- LVGL 9

Telemetry
- JSON over USB Serial
- LabVIEW compatible