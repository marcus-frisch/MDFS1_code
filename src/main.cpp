#include <Arduino.h>
#include <Harley.h>
#include <Marcus.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Encoder.h>

Servo tubeServo1;
Servo tubeServo2;
ESP32Encoder tubeEncoder;

// tube length positions (these are placeholder values and completely wrong)
#define T_FULL_RETRACT 0
#define T_SEED_1 50
#define T_SEED_2 100
#define T_SEED_3 150
#define T_SEED_4 200
#define T_SEED_5 250
#define T_SEED_6 300

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  // these are the two servo motors responcible for extending/retracting the tube
  tubeServo1.attach(12);
  tubeServo2.attach(13);
  // ensure the servos are stationary upon startup
  tubeServo1.write(90);
  tubeServo2.write(90);

  tubeEncoder.attachHalfQuad(23, 22);
  tubeEncoder.setCount(0);

  initialiseOled();
  initialiseJoystickIR();

  installTube(tubeServo1, tubeServo2);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // marcusBlink(500);
  // harleyBlink(250);

  // Serial.println("Touch: " + String(touchRead(4)) + " M: " + String(readButton()) + " State: " + String(state));
}
