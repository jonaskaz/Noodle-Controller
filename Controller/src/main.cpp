#include <Arduino.h>
#include <StepMotor.h>
#include <MultiStepper.h>
#include <ArduinoJson.h>
#include <ButtonController.h>

#define yMaxPin 10
#define xMaxPin 6
#define xMinPin 7
#define motorInterfaceType 1

const int stepPins[3] = {3, 5, 9};
const int dirPins[3] = {2, 4, 8};

StepMotor step = StepMotor(motorInterfaceType, stepPins, dirPins);

// Button buttonUp(10);
// Button buttonDown(11);
Button buttonLeft(12);
Button buttonRight(13);
// Button buttonStart(12);
// Button buttonStop(13);

ButtonController controller;

void setup()
{
    Serial.begin(112500);
    int startingPos[2] = {0, 0};
    step.setup(1000, 500, 1000, 1000, startingPos);
    delay(5000);
    step.calibrate(yMaxPin, xMinPin, xMaxPin);
}

void loop()
{
    // stepper.goTo(controller.horizontalButtonControl(buttonLeft, buttonRight));

    if (Serial.available() > 0)
    {
        int mode = Serial.parseInt();
        String flavor = Serial.readStringUntil('\n');
        String toppings = Serial.readStringUntil('\n');
        StaticJsonDocument<200> doc;
        deserializeJson(doc, toppings);
        JsonArray toppingsArray = doc.as<JsonArray>();
        switch (mode)
        {
        case 0:
            break;
        case 1:
            break;
        default:
            break;
        }
        String beef = "beef";
        flavor.trim();
        if (flavor.equals(beef))
        {
            step.goToB(75, 75);
            Serial.println(flavor);
        }
        else
        {
            ;
        }
    }
}