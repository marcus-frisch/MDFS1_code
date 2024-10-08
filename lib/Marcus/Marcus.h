#include <ESP32Servo.h>
void initialiseOled();
void initialiseJoystickIR();
bool readButton();
void marcusBlink(int time);
int servoJoystickX();
void marcusServoTest(Servo &servoMotor);
void installTube(Servo &servoMotor);
