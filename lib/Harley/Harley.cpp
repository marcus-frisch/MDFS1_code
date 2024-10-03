#include <Arduino.h>
#include <ESP32Servo.h>
#include "Harley.h"

#define LED 2

void harleyBlink(int time)
{
    pinMode(2, OUTPUT);
    delay(time);
    digitalWrite(2, HIGH);
    delay(time);
    digitalWrite(2, LOW);
    delay(time);
}

void harleyServoTest(Servo servoMotor)
{
    // Servo spins forward at full speed for 1 second.
    servoMotor.write(180);
    delay(2000);
    // Servo is stationary for 1 second.
    servoMotor.write(90);
    delay(1000);
    // Servo spins in reverse at full speed for 1 second.
    servoMotor.write(0);
    delay(2000);
    // Servo is stationary for 1 second.
    servoMotor.write(90);
    delay(1000);
}