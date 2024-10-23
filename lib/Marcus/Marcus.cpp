#include "Marcus.h"

static int receivedJoystickX = 2048;
static int receivedJoystickY = 0;
static int receivedTouchReading = 0;

String oledTop = "Top";
String oledBottom = "Bottom";

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

void updateRecievedRemote(int joyX, int joyY, int touch)
{
    receivedJoystickX = joyX;
    receivedJoystickY = joyY;
    receivedTouchReading = touch;
}

bool readButton() // this reads one of the touch pins on an esp32
{
    static int buttonRest = receivedTouchReading; // define what the capacitance is when no one is touching the button

    static bool pressDetected = false; // has any present touch already been detected

    if (receivedTouchReading < buttonRest - 30 && !pressDetected) // detect a press (that hasn't already been detected)
    {
        pressDetected = true;
        return 1;
    }
    else if (receivedTouchReading > buttonRest - 20 && pressDetected) // reset and prepare for a future press when no longer pressed
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

void printText(String topLine, String bottomLine)
{
    oledTop = topLine;
    oledBottom = bottomLine;
}

void statusLed(bool status)
{
    int interval = 200;
    static unsigned long lastFlash = 0;

    if (status)
    {
        interval = 800;
    }

    if (millis() >= lastFlash + interval)
    {
        digitalWrite(LED, !digitalRead(LED));
    }
}

int servoJoystickX() // return the reading of a joysticks X axis, specifically for servo control
{
    int value = receivedJoystickX;
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

void installTube(Servo &servoMotor, Servo &servoMotor1, ESP32Encoder &rotEncoder) // used to aid with the installation and homing of a tube upon startup
{
    static int installState = 0; // 0 manual install (load in tube), 1 auto homing (position tube into bottom of arm assembly)

    while (installState < 2)
    {
        if (installState == 0)
        {
            if (servoJoystickX() < 88)
            {
                printText("LTube", "Extending");
            }
            else if (servoJoystickX() > 92)
            {
                printText("LTube", "Retracting");
            }
            else
            {
                printText("LTube", "Idle");
            }

            servoMotor.write(servoJoystickX());
            servoMotor1.write(servoJoystickX());

            if (readButton())
            {
                installState++;
            }
        }
        else if (installState == 1)
        {
            printText("AutoHome", "Please wait...");

            if (digitalRead(IR))
            {
                servoMotor.write(110);
                servoMotor1.write(110);
            }
            else
            {
                servoMotor.write(90);
                servoMotor1.write(90);
                rotEncoder.setCount(0);

                installState++;
                printText("Done", "Tube loaded");
            }
        }
    }
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