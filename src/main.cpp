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

// #include "../../test/Test.h"


#include "../../include/pinDef.h"
#include "../../include/libDef.h"


#define MAXSPEED 500
int STEPS = 500;


Servo tubeServo0;
Servo tubeServo1;
Servo hingeServo;
Servo incinerateServo;
ESP32Encoder tubeEncoder;
AccelStepper fr(AccelStepper::DRIVER, STEP1, DIR1);
AccelStepper fl(AccelStepper::DRIVER, STEP2, DIR2);
AccelStepper br(AccelStepper::DRIVER, STEP3, DIR3);
AccelStepper bl(AccelStepper::DRIVER, STEP4, DIR4);
MultiStepper steppers;

long positions[4];


// tube length positions (these are placeholder values and completely wrong)
// #define T_FULL_RETRACT 0
// #define T_SEED_1 50
// #define T_SEED_2 100
// #define T_SEED_3 150
// #define T_SEED_4 200
// #define T_SEED_5 250
// #define T_SEED_6 300


void setup()
{
  setupPins();//function in the pindef file whihc sets the input or output or other values of a pin
  Serial.print("1");
  Serial.begin(115200);

  // these are the two servo motors responcible for extending/retracting the tube
  // tubeServo0.attach(12);
  // tubeServo1.write(0);

  // tubeEncoder.attachHalfQuad(23, 22);
  // tubeEncoder.setCount(0);

  // hingeServo.attach(HINGE);

  // initialiseOled();
  // initialiseJoystickIR();

  fl.setMaxSpeed(MAXSPEED);
  fr.setMaxSpeed(MAXSPEED);
  bl.setMaxSpeed(MAXSPEED);
  br.setMaxSpeed(MAXSPEED);

  // setupSteppers(fl, fr, bl, br);
  steppers.addStepper(fl);
  steppers.addStepper(fr);
  steppers.addStepper(bl);
  steppers.addStepper(br);
  // setupMultiSteppers(steppers, fl, fr, bl, br);
  hingeServo.write(80);


  // installTube(tubeServos, tubeEncoder);
}


void run();
bool setTubePos(long desiredCount, ESP32Encoder &rotEncoder, Servo &servoMotor, Servo &servoMotor1);
void blocking_setTubePos(long desiredCount, ESP32Encoder &rotEncoder, Servo &servoMotor, Servo &servoMotor1);


void loop()
{
  // run();
  // setupMultiSteppers(steppers, fl, fr, bl, br);

  // moveForward(100, steppers);

  // delay(1000);
  // moveForward(100, steppers);
  // delay(1000);

  STEPS+=100;
  positions[0] = STEPS;
  positions[1] = STEPS;
  positions[2] = STEPS;
  positions[3] = STEPS;

  steppers.moveTo(positions);
  steppers.runSpeedToPosition();


  hingeServo.write(100);
  // hingeMovement(180, hingeServo);



  // blocking_setTubePos(T_SEED_1, tubeEncoder, tubeServos); // extend tube to seed 1 collection position

  // harleyBlink(250);
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
    moveForward(500, steppers);

    incinerate(incinerateServo);


}


bool setTubePos(long desiredCount, ESP32Encoder &rotEncoder, Servo &servoMotor, Servo &servoMotor1)
{ // takes a known counter value and sets the tube to that position (extending/retracting) - returns true once tube is in position

    if (rotEncoder.getCount() > desiredCount)
    {
        servoMotor.write(110); // speeds should be tested & updated
        servoMotor1.write(110);
    }
    else if (rotEncoder.getCount() < desiredCount)
    {
        servoMotor.write(70); // speeds should be tested & updated
        servoMotor1.write(70);
    }
    else
    {
        servoMotor.write(90);
        servoMotor1.write(90);
        return true;
    }
    return false;
}

void blocking_setTubePos(long desiredCount, ESP32Encoder &rotEncoder, Servo &servoMotor, Servo &servoMotor1) // blocks other code and only allows tube to be positioned (used for testing)
{
    bool tubeDone = false;

    do
    {
        tubeDone = setTubePos(desiredCount, rotEncoder, servoMotor, servoMotor1);
    } while (!tubeDone);
}