#include "../../include/libDef.h"

#ifndef PINDEF_H
#define PINDEF_H

#define DIR 4
#define STEP 15
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

}


#endif