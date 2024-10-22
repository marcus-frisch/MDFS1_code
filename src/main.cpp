#include <Arduino.h>
#include <Harley.h>
#include <Marcus.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Encoder.h>

Servo tubeServos;
Servo hingeServo;
ESP32Encoder tubeEncoder;

// tube length positions (these are placeholder values and completely wrong)
#define T_FULL_RETRACT 0
#define T_SEED_1 50
#define T_SEED_2 100
#define T_SEED_3 150
#define T_SEED_4 200
#define T_SEED_5 250
#define T_SEED_6 300




// void setup()
// {
//   Serial.begin(115200);

//   // these are the two servo motors responcible for extending/retracting the tube
//   tubeServos.attach(12);
//   // ensure the servos are stationary upon startup
//   tubeServos.write(0);

//   // tubeEncoder.attachHalfQuad(23, 22);
//   // tubeEncoder.setCount(0);

//   // initialiseOled();
//   // initialiseJoystickIR();

//   // installTube(tubeServos, tubeEncoder);
// }


// void loop()
// {
//   // put your main code here, to run repeatedly:
//     tubeServos.write(0);
//     delay(2000);
//     tubeServos.write(90);
//     delay(2000);
//     tubeServos.write(180);
//     delay(2000);




//   // blocking_setTubePos(T_SEED_1, tubeEncoder, tubeServos); // extend tube to seed 1 collection position

//   // harleyBlink(250);
// }















// code for woring stepper
#define DIR 2
#define STEP 15


#include <AccelStepper.h>

AccelStepper stepper3(AccelStepper::DRIVER, STEP, DIR);

void setup()
{  
    stepper3.setMaxSpeed(1000.0);
    stepper3.setAcceleration(300.0);
    stepper3.moveTo(1000); 
}

void loop()
{
    stepper3.runToPosition();
    stepper3.moveTo(1000); 

}