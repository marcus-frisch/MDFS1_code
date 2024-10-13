#ifndef MARCUS_H
#define MARCUS_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Encoder.h>
#include "../../include/pinDef.h"

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

/**
 * @brief blink onboard LED at time interval (used for debugging)
 */
void marcusBlink(int time);

/**
 * @return reading from joystick X axis within servo.write() range
 */
int servoJoystickX();

/**
 * @brief test servo object
 */
void marcusServoTest(Servo &servoMotor, Servo &servoMotor1);

/**
 * @brief initial install of tube into the robot (requires operator assistance)
 */
void installTube(Servo &servoMotor, Servo &servoMotor1, ESP32Encoder &rotEncoder);

/**
 * @brief set the tube to a known position by known rotary encoder counter values
 * @return if tube is in desired location
 */
bool setTubePos(long desiredCount, ESP32Encoder &rotEncoder, Servo &servoMotor, Servo &servoMotor1);

/**
 * @brief same as setTubePos() but blocks other code from running until tube is in desired position (used for debugging)
 */
void blocking_setTubePos(long desiredCount, ESP32Encoder &rotEncoder, Servo &servoMotor, Servo &servoMotor1);

#endif