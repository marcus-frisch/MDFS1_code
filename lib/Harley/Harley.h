#include <ESP32Servo.h>
#include "../../include/pinDef.h"

#define DIR 15
#define STEP 2

void hingeMovement(int degree, Servo &servo);


void stepper(int steps);
