#include <Arduino.h>
#include <Chef.h>
#include <ArduinoJson.h>

#define yMaxPin 10
#define xMaxPin 6
#define xMinPin 7
#define motorInterfaceType 1

const int stepPins[3] =  {3, 5, 9};
const int dirPins[3] = {2, 4, 8};

StepMotor step = StepMotor(motorInterfaceType, stepPins, dirPins);
Chef chef = Chef();
StaticJsonDocument<200> doc;

void setup()
{
    Serial.begin(112500);
    int startingPos[2] = {0,0};
    step.setup(1000, 500, 1000, 1000, startingPos);
    delay(5000);
    step.calibrate(yMaxPin, xMinPin, xMaxPin);
}

void loop()
{
    if (Serial.available() > 0) {
        int mode = Serial.parseInt();
        String flavor = Serial.readStringUntil('\n');
        flavor.trim();
        char flavorChar[50];
        flavor.toCharArray(flavorChar, 50);
        String toppings = Serial.readStringUntil('\n');
        deserializeJson(doc, toppings);
        JsonArray toppingsArray = doc.as<JsonArray>();
        switch (mode) {
            case 0:
                break;
            case 1:
                chef.make(flavorChar, toppingsArray);
                break;
            default:
                break;
        }
    }
}