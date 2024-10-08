#ifndef MARCUS_H
#define MARCUS_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**
 * @brief Initilaises the olde screen
 */
void initialiseOled();

/**
 * @brief initialises the joystick
 */
void initialiseJoystickIR();

/**
 * @brief reads the button state
 * @return return true if button pressed, false otherwise
 */
bool readButton();


void marcusBlink(int time);
int servoJoystickX();
void marcusServoTest(Servo &servoMotor);
void installTube(Servo &servoMotor);


#endif