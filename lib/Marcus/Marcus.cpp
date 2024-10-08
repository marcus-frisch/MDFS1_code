#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Marcus.h"

#define LED 2
#define JOYX 32
#define JOYY 33
#define IR 23
#define BUTTON 4
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initialiseOled()
{

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("MDFS");
    display.invertDisplay(false);
    display.display();
}

void initialiseJoystickIR()
{
    pinMode(IR, INPUT);
    pinMode(JOYX, INPUT);
    pinMode(JOYY, INPUT);
    pinMode(BUTTON, INPUT);
}

bool readButton()
{
    static int buttonRest = touchRead(BUTTON);

    static bool pressDetected = false;

    if (touchRead(BUTTON) < buttonRest - 30 && !pressDetected)
    {
        pressDetected = true;
        return 1;
    }
    else if (touchRead(BUTTON) > buttonRest - 20 && pressDetected)
    {
        pressDetected = false;
    }

    return 0;
}

void marcusBlink(int time)
{
    // Serial.println("Blink!");
    pinMode(2, OUTPUT);
    delay(time);
    digitalWrite(2, HIGH);
    delay(time);
    digitalWrite(2, LOW);
    delay(time);
}

int servoJoystickX()
{
    int value = analogRead(JOYX);
    value = map(value, 0, 4095, 0, 180);

    if (value < 122) // yes this IF stuff is weird, but my joystick in neutral position outputs 122 when 90 is expected.
    {
        value = map(value, 0, 122, 0, 90);
    }
    else if (value > 122)
    {
        value = map(value, 122, 180, 90, 180);
    }
    else
    {
        value = 90;
    }

    return value;
}

void marcusServoTest(Servo &servoMotor)
{
    // Servo spins forward at full speed for 1 second.
    servoMotor.write(100);
    Serial.println("Forwards!");
    delay(2000);
    // Servo is stationary for 1 second.
    servoMotor.write(90);
    Serial.println("Stopped!");
    delay(1000);
    // Servo spins in reverse at full speed for 1 second.
    servoMotor.write(80);
    Serial.println("Backwards!");
    delay(2000);
    // Servo is stationary for 1 second.
    servoMotor.write(90);
    Serial.println("Stopped!");
    delay(1000);
}

void installTube(Servo &servoMotor)
{
    static int installState = 0; // 0 manual, 1 auto homing

    while (installState < 2)
    {
        if (installState == 0)
        {
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setCursor(0, 0);
            display.setTextSize(2);
            display.println("Load Tube");
            display.setTextSize(1);
            display.setCursor(0, 20);
            display.println("Use Joystick, then\npush button.");

            String tubeMovement = "";
            if (servoJoystickX() < 88)
            {
                tubeMovement = "Extending";
            }
            else if (servoJoystickX() > 92)
            {
                tubeMovement = "Retracting";
            }
            else
            {
                tubeMovement = "Idle";
            }
            display.setTextSize(2);
            display.setCursor(0, 40);
            display.println(tubeMovement);
            display.setTextSize(1);
            display.setCursor(0, 55);
            display.println(String(servoJoystickX()));

            display.display();

            servoMotor.write(servoJoystickX());

            if (readButton())
            {
                installState++;
            }
        }
        else if (installState == 1)
        {
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setCursor(0, 0);
            display.setTextSize(2);
            display.println("Auto Home");
            display.setTextSize(1);
            display.setCursor(0, 20);
            display.println("Give us a sec");
            display.invertDisplay(true);
            display.display();

            if (digitalRead(IR))
            {
                servoMotor.write(110);
            }
            else
            {
                servoMotor.write(90);
                installState++;
                display.invertDisplay(false);
                display.clearDisplay();
                display.setCursor(0, 0);
                display.setTextSize(1);
                display.println("Next stage");
                display.display();
            }
        }
    }
}
