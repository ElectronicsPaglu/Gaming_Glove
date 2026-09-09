Gaming Glove using Arduino Leonardo

Introduction
This gaming glove uses an ADXL345 accelerometer mounted on a wristband. Tilting your hand along the X and Y axes triggers key presses, letting you control games like Subway Surfers, which use W, A, S, D for movement. I mapped the X-axis to 'A' and 'D', and the Y-axis to 'W' and 'S'. Only four keys are used here for simplicity, but the ADXL345 can support much more — feel free to expand on it.

Note: Unlike the Uno/Nano, the Arduino Leonardo has a built-in ATmega32u4 chip with native USB HID support, so it can act as a keyboard directly using the Keyboard.h library — no firmware flashing required.

Connections
Wire the ADXL345 to the Leonardo via I2C: VCC → 5V/3.3V, GND → GND, SDA → SDA, SCL → SCL.
(Add your own wiring photo here.)

Steps to get started

1)Wire the ADXL345 to your Leonardo as shown above.
2)Clone this repository or download the ZIP.
3)Open main_code.ino in the Arduino IDE and upload it.
4)Tune the tilt-angle thresholds in the code to match your hand's natural resting position.
5)Bind your game's controls to W, A, S, D.
6)Put on the glove and start playing.