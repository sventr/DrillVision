DrillVision Telemetry Protocol

Transport:
USB Serial

Format:
JSON

Example:

{
  "device":"DrillVision",
  "version":"4.17",
  "timestamp":15230,
  "roll":0.12,
  "pitch":-0.35,
  "battery":100.0,
  "temperature":23.5,
  "wifi":false,
  "usb":false,
  "charging":false,
  "state":"IM LOT"
}
LabVIEW Integration

Serial Port
115200 Baud

One JSON object per line.