#ifndef HARLEY_H
#define HARLEY_H

#include "../../include/libDef.h"
#include "../../include/pinDef.h"


void hingeMovement(int degree, Servo &servo);

void setupMultiSteppers(MultiStepper &steppers, AccelStepper &fl, AccelStepper &fr, AccelStepper &bl, AccelStepper &br);

void setupSteppers(AccelStepper &fl, AccelStepper &fr, AccelStepper &bl, AccelStepper &br);

void moveForward(int step, MultiStepper &steppers);

void moveBackwards(long step, MultiStepper &steppers);

void moveLeft(long step, MultiStepper &steppers);

void moveRight(long step, MultiStepper &steppers);

void moveDFR(long step, MultiStepper &steppers);

void moveDFl(long step, MultiStepper &steppers);

void moveDFR(long step, MultiStepper &steppers);

void moveDBL(long step, MultiStepper &steppers);

void moveDBR(long step, MultiStepper &steppers);

void rotateClockwise(long step, MultiStepper &steppers);

void rotateAntiClockwise(long step, MultiStepper &steppers);

#endif