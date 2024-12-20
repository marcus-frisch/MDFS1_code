#include "Harley.h"

void hingeMovement(int degree, Servo &servo){
    servo.write(degree);
}

void setupMultiSteppers(MultiStepper &steppers,AccelStepper &fl, AccelStepper &fr, AccelStepper &bl, AccelStepper &br){
    steppers.addStepper(fl);
    steppers.addStepper(fr);
    steppers.addStepper(bl);
    steppers.addStepper(br);
}


void setupSteppers(AccelStepper &fl, AccelStepper &fr, AccelStepper &bl, AccelStepper &br){
    fl.setMaxSpeed(1000);
    // fl.setAcceleration(300);


    fr.setMaxSpeed(1000);
    // fr.setAcceleration(300);

    bl.setMaxSpeed(1000);
    // bl.setAcceleration(300);

    br.setMaxSpeed(1000);
    // br.setAcceleration(300);

}


void moveForward(long step, MultiStepper &steppers){
    long positions[4] = {step, step, step, step}; 
    steppers.moveTo(positions);
    steppers.runSpeedToPosition(); //blocking function
}

void moveBackwards(long step, MultiStepper &steppers){
    long positions[4] = {-step, -step, -step, -step};
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
}

void moveLeft(long step, MultiStepper &steppers){
    long positions[4] = {step, -step, -step, step};
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
}

void moveRight(long step, MultiStepper &steppers){
    long positions[4] = {-step, step, step, -step};
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
}

void moveDFR(long step, MultiStepper &steppers){ //move diagonal front right
    long positions[4] = {step, 0, 0, step};
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
}

void moveDFl(long step, MultiStepper &steppers){ //move diagonal front left
    long positions[4] = {0, step, step, 0};
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
}

void moveDBL(long step, MultiStepper &steppers){ //move diagonal back right
    long positions[4] = {-step, 0, 0, -step};
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
}

void moveDBR(long step, MultiStepper &steppers){ //move diagonal back left
    long positions[4] = {0, -step, -step, 0};
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
}

void rotateClockwise(long step, MultiStepper &steppers){
    long positions[4] = {0, -step, -step, 0};
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
}

void rotateAntiClockwise(long step, MultiStepper &steppers){
    long positions[4] = {-step, step, -step, step};
    steppers.moveTo(positions);
    steppers.runSpeedToPosition();
}

void incinerate(Servo &servo){
    servo.write(90);
    delay(1000);
    servo.write(0);
}





// void setup()
// {  
//     stepper3.setMaxSpeed(1000.0);
//     stepper3.setAcceleration(300.0);
//     stepper3.moveTo(1000); 
// }

// void loop()
// {
//     stepper3.runToPosition();
//     stepper3.moveTo(1000); 

// }
