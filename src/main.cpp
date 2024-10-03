#include <Arduino.h>
#include <Harley.h>
#include <Marcus.h>
#include <ESP32Servo.h>

Servo myservo;

void setup()
{
  // put your setup code here, to run once:

  // The servo control wire is connected to Arduino D2 pin.
  myservo.attach(12);
  // Servo is stationary.
  myservo.write(90);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // marcusServoTest(myservo);  // test if a servo is working
  // marcusBlink(500);
  harleyBlink(250);
}
