#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo;

int pos = 0;

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

  // Servo spins forward at full speed for 1 second.
  myservo.write(180);
  delay(2000);
  // Servo is stationary for 1 second.
  myservo.write(90);
  delay(500);
  // Servo spins in reverse at full speed for 1 second.
  myservo.write(0);
  delay(2000);
  // Servo is stationary for 1 second.
  myservo.write(90);
  delay(500);
}
