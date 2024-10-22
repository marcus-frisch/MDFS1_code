#include <Arduino.h>
#include "Harley.h"

void hingeMovement(int degree, Servo &servo){
    servo.write(degree);
}

void stepper(){


}