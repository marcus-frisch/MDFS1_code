
#include "Marcus.h"
#include "../include/pinDef.h"


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

void initialiseJoystickIR() // initialise pins we need
{
    pinMode(IR, INPUT);
    pinMode(JOYX, INPUT);
    pinMode(JOYY, INPUT);
    pinMode(BUTTON, INPUT);
}

bool readButton() // this reads one of the touch pins on an esp32
{
    static int buttonRest = touchRead(BUTTON); // define what the capacitance is when no one is touching the button

    static bool pressDetected = false; // has any present touch already been detected

    if (touchRead(BUTTON) < buttonRest - 30 && !pressDetected) // detect a press (that hasn't already been detected)
    {
        pressDetected = true;
        return 1;
    }
    else if (touchRead(BUTTON) > buttonRest - 20 && pressDetected) // reset and prepare for a future press when no longer pressed
    {
        pressDetected = false;
    }

    return 0;
}

void marcusBlink(int time) // blink onboard LED (used for debugging/testing)
{
    // Serial.println("Blink!");
    pinMode(2, OUTPUT);
    delay(time);
    digitalWrite(2, HIGH);
    delay(time);
    digitalWrite(2, LOW);
    delay(time);
}

int servoJoystickX() // return the reading of a joysticks X axis, specifically for servo control
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

void marcusServoTest(Servo &servoMotor) // test a servo motors functionality
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

void installTube(Servo &servoMotor) // used to aid with the installation and homing of a tube upon startup
{
    static int installState = 0; // 0 manual install (load in tube), 1 auto homing (position tube into bottom of arm assembly)

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
