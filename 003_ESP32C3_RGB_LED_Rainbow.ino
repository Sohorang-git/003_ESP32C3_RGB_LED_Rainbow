const int RGB_LED_PIN = 8;
const int BOOT_BUTTON_PIN = 9;
const int MAX_BRIGHTNESS = 48;
const unsigned long FRAME_INTERVAL_MS = 20;

uint16_t hue = 0;
unsigned long lastFrameAt = 0;

void hsvToRgb(uint16_t hueValue, uint8_t saturation, uint8_t value,
              uint8_t &red, uint8_t &green, uint8_t &blue) {
  uint8_t region = hueValue / 43;
  uint8_t remainder = (hueValue - (region * 43)) * 6;

  uint8_t p = (value * (255 - saturation)) >> 8;
  uint8_t q = (value * (255 - ((saturation * remainder) >> 8))) >> 8;
  uint8_t t = (value * (255 - ((saturation * (255 - remainder)) >> 8))) >> 8;

  switch (region) {
    case 0:
      red = value;
      green = t;
      blue = p;
      break;
    case 1:
      red = q;
      green = value;
      blue = p;
      break;
    case 2:
      red = p;
      green = value;
      blue = t;
      break;
    case 3:
      red = p;
      green = q;
      blue = value;
      break;
    case 4:
      red = t;
      green = p;
      blue = value;
      break;
    default:
      red = value;
      green = p;
      blue = q;
      break;
  }
}

void turnLedOff() {
  neopixelWrite(RGB_LED_PIN, 0, 0, 0);
}

void drawRainbowFrame() {
  uint8_t red;
  uint8_t green;
  uint8_t blue;

  hsvToRgb(hue, 255, MAX_BRIGHTNESS, red, green, blue);
  neopixelWrite(RGB_LED_PIN, red, green, blue);

  hue = (hue + 1) % 256;
}

void setup() {
  pinMode(BOOT_BUTTON_PIN, INPUT_PULLUP);
  turnLedOff();
}

void loop() {
  bool buttonPressed = digitalRead(BOOT_BUTTON_PIN) == LOW;

  if (buttonPressed) {
    turnLedOff();
    delay(10);
    return;
  }

  if (millis() - lastFrameAt >= FRAME_INTERVAL_MS) {
    drawRainbowFrame();
    lastFrameAt = millis();
  }
}
