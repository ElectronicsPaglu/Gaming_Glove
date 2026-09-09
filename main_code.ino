/*
  Gaming Glove using Arduino Leonardo + ADXL345
  ------------------------------------------------
  Reads tilt on X and Y axes from the ADXL345 accelerometer
  and sends W/A/S/D keypresses using the Leonardo's native
  USB HID support (Keyboard.h). No firmware flashing needed.

  Wiring (I2C):
    ADXL345 VCC -> Leonardo 3.3V (or 5V if your breakout supports it)
    ADXL345 GND -> Leonardo GND
    ADXL345 SDA -> Leonardo SDA (near AREF, or pin 2 on some boards)
    ADXL345 SCL -> Leonardo SCL (near AREF, or pin 3 on some boards)
*/

#include <Wire.h>
#include <Keyboard.h>

const int ADXL345_ADDR = 0x53; // Default I2C address for ADXL345

int16_t x, y, z;

// Tilt thresholds in raw accelerometer units — TUNE THESE to your glove's resting position
const int TILT_THRESHOLD = 60;

// Track currently held key so we only press/release on state changes
char currentKey = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Wake up ADXL345 (it starts in standby mode)
  writeRegister(0x2D, 0x08); // Set POWER_CTL register: measure mode

  // Optional: set data format (full resolution, +/-2g range)
  writeRegister(0x31, 0x08);

  Keyboard.begin();
}

void loop() {
  readAccel();

  char keyToPress = 0;

  // X-axis controls A / D
  if (x > TILT_THRESHOLD) {
    keyToPress = 'd';
  } else if (x < -TILT_THRESHOLD) {
    keyToPress = 'a';
  }
  // Y-axis controls W / S (only checked if X-axis isn't already triggering)
  else if (y > TILT_THRESHOLD) {
    keyToPress = 'w';
  } else if (y < -TILT_THRESHOLD) {
    keyToPress = 's';
  }

  // Only send key events on change, so we don't spam repeat presses
  if (keyToPress != currentKey) {
    if (currentKey != 0) {
      Keyboard.release(currentKey);
    }
    if (keyToPress != 0) {
      Keyboard.press(keyToPress);
    }
    currentKey = keyToPress;
  }

  delay(50); // Small debounce/read interval
}

void writeRegister(byte reg, byte value) {
  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void readAccel() {
  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(0x32); // Start at DATAX0 register
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345_ADDR, 6, true);

  x = Wire.read() | (Wire.read() << 8);
  y = Wire.read() | (Wire.read() << 8);
  z = Wire.read() | (Wire.read() << 8);
}