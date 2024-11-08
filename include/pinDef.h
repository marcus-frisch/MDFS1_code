// #include "../../include/libDef.h"
#include <Arduino.h>

#ifndef PINDEF_H
#define PINDEF_H

#define DIR1 0
#define STEP1 15
#define DIR2 16
#define STEP2 4
#define DIR3 5
#define STEP3 7
#define DIR4 19
#define STEP4 18
#define HINGE 21


#define LED 2
#define JOYX 32
#define JOYY 33
#define IR 34
#define BUTTON 2
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


inline void setupPins(){
    pinMode(LED, OUTPUT);
    pinMode(JOYX, OUTPUT);
    pinMode(JOYY, OUTPUT);
    pinMode(IR, OUTPUT);

    pinMode(DIR1, OUTPUT);
    pinMode(STEP1, OUTPUT);
    pinMode(DIR2, OUTPUT);
    pinMode(STEP2, OUTPUT);
    pinMode(DIR3, OUTPUT);
    pinMode(STEP3, OUTPUT);
    pinMode(DIR4, OUTPUT);
    pinMode(STEP4, OUTPUT);

}


#endif