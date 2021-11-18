#include <Arduino.h>
#include <StepMotor.h>
#include <MultiStepper.h>
#include <ArduinoJson.h>
#include <ezButton.h>

#define yMaxPin 10
#define xMaxPin 6
#define xMinPin 7
#define motorInterfaceType 1

const int stepPins[3] = {3, 5, 9};
const int dirPins[3] = {2, 4, 8};

StepMotor step = StepMotor(motorInterfaceType, stepPins, dirPins);

ezButton buttonLeft(12);
ezButton buttonRight(13);

bool goingLeft = false;
bool goingRight = false;

void setup()
{
    Serial.begin(112500);
    buttonLeft.setDebounceTime(50);  // set debounce time to 50 milliseconds
    buttonRight.setDebounceTime(50); // set debounce time to 50 milliseconds
    int startingPos[2] = {0, 0};
    step.setup(1000, 500, 1000, 1000, startingPos);
    delay(5000);
    // step.calibrate(yMaxPin, xMinPin, xMaxPin);
}

void loop()
{
    buttonLeft.loop();
    buttonRight.loop();

    if (buttonLeft.isPressed())
        goingLeft = true;

    if (buttonLeft.isReleased())
        goingLeft = false;

    if (buttonRight.isPressed())
        goingRight = true;

    if (buttonRight.isReleased())
        goingRight = false;

    if (goingLeft)
    {
        // Serial.println("L");
        step.goTo(0, 0);
    }

    if (goingRight)
    {
        // Serial.println("R");
        step.goTo(100, 0);
    }

    // if (Serial.available() > 0)
    // {
    //     int mode = Serial.parseInt();
    //     String flavor = Serial.readStringUntil('\n');
    //     String toppings = Serial.readStringUntil('\n');
    //     StaticJsonDocument<200> doc;
    //     deserializeJson(doc, toppings);
    //     JsonArray toppingsArray = doc.as<JsonArray>();
    //     switch (mode)
    //     {
    //     case 0:
    //         break;
    //     case 1:
    //         break;
    //     default:
    //         break;
    //     }
    //     String beef = "beef";
    //     flavor.trim();
    //     if (flavor.equals(beef))
    //     {
    //         step.goToB(75, 75);
    //         Serial.println(flavor);
    //     }
    //     else
    //     {
    //         ;
    //     }
    // }
}