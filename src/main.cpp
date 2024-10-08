#include <Arduino.h>
#include <Harley.h>
#include <Marcus.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Servo tubeServo;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  // The servo control wire is connected to Arduino D2 pin.
  tubeServo.attach(12);
  // Servo is stationary.
  tubeServo.write(90);

  initialiseOled();
  initialiseJoystickIR();

  installTube(tubeServo);
}

void loop()
{
  // put your main code here, to run repeatedly:

  // marcusBlink(500);
  // harleyBlink(250);

  // Serial.println("Touch: " + String(touchRead(4)) + " M: " + String(readButton()) + " State: " + String(state));
}
