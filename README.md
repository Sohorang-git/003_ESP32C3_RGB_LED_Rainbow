# 003 ESP32-C3 RGB LED Rainbow

ESP32-C3-DevKitM-1 built-in WS2812 RGB LED rainbow demo.

## Hardware

- Built-in WS2812 RGB LED: GPIO8
- BOOT button: GPIO9

## Behavior

- The RGB LED cycles smoothly through a rainbow.
- Press the BOOT button to toggle the LED off.
- Press it again to resume the rainbow animation.

## Build and Upload

```powershell
arduino-cli compile --fqbn esp32:esp32:esp32c3 .
arduino-cli upload -p COM3 --fqbn esp32:esp32:esp32c3 .
```
