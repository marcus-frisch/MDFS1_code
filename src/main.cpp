#include <Harley.h>
#include <Marcus.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <ESP32Servo.h>
#include <Arduino.h>
#include <ESP32Encoder.h>

#include "../../include/pinDef.h"
#include "../../include/libDef.h"



Servo tubeServo0;
Servo tubeServo1;
Servo hingeServo;
ESP32Encoder tubeEncoder;
AccelStepper fr(AccelStepper::DRIVER, STEP, DIR);
AccelStepper fl(AccelStepper::DRIVER, STEP, DIR);
AccelStepper br(AccelStepper::DRIVER, STEP, DIR);
AccelStepper bl(AccelStepper::DRIVER, STEP, DIR);
MultiStepper steppers;


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
    setupPins();//function in the pindef file whihc sets the input or output or other values of a pin

//   Serial.begin(115200);

  // these are the two servo motors responcible for extending/retracting the tube
  tubeServo0.attach(12);
  tubeServo1.write(0);

  tubeEncoder.attachHalfQuad(23, 22);
  tubeEncoder.setCount(0);

  initialiseOled();
  initialiseJoystickIR();

  setupSteppers(fl, fr, bl, br);
  setupMultiSteppers(steppers, fl, fr, bl, br);

  // installTube(tubeServos, tubeEncoder);
}

void run(){
    // picks up first ball
    hingeMovement(180, hingeServo);
    blocking_setTubePos(100, tubeEncoder, tubeServo0, tubeServo1);//tube movement out
    hingeMovement(90, hingeServo);
    blocking_setTubePos(0, tubeEncoder, tubeServo0, tubeServo1);//tube movement in 

    
    //moves to and picks up second ball
    moveForward(500, steppers);
    hingeMovement(180, hingeServo);
    blocking_setTubePos(300, tubeEncoder, tubeServo0, tubeServo1);//tube movement out 
    hingeMovement(90, hingeServo);
    blocking_setTubePos(0, tubeEncoder, tubeServo0, tubeServo1);//tube movement in 

    
    //move to and picks up thrid ball
    moveForward(500, steppers);
    hingeMovement(180, hingeServo);
    blocking_setTubePos(100, tubeEncoder, tubeServo0, tubeServo1);//tube movement out 
    hingeMovement(90, hingeServo);
    blocking_setTubePos(0, tubeEncoder, tubeServo0, tubeServo1);//tube movement in 

    rotateClockwise(500, steppers);





}





void loop()
{


  // blocking_setTubePos(T_SEED_1, tubeEncoder, tubeServos); // extend tube to seed 1 collection position

  // harleyBlink(250);
}
