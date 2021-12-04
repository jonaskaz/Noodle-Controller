#include <Arduino.h>
#include <Chef.h>
#include <ArduinoJson.h>

#define yMaxPin 8
#define xMaxPin 10
#define xMinPin 9
#define motorInterfaceType 1

const int stepPins[3] =  {3, 5, 7};
const int dirPins[3] = {2, 4, 6};
int flavorPins[4] = {11, 11, 11, 11};
int toppingPins[4] = {11, 11, 11, 11};


StepMotor step = StepMotor(motorInterfaceType, stepPins, dirPins);
Chef chef = Chef();
StaticJsonDocument<200> doc;

void setup()
{
    Serial.begin(115200);
    int startingPos[2] = {0,0};
    step.setup(1000, 500, 1000, 1000, startingPos);
    chef.setup(flavorPins, toppingPins, step, 20);
    delay(5000);
    step.calibrate(yMaxPin, xMinPin, xMaxPin);
    delay(2000);
}

char readFlavor(){
    String flavor = Serial.readStringUntil('\n');
    flavor.trim();
    char flavorChar[50];
    flavor.toCharArray(flavorChar, 50);
    char ptr = flavorChar[0];
    return ptr;
}

JsonArray readToppings(){
    String toppings = Serial.readStringUntil('\n');
    deserializeJson(doc, toppings);
    return doc.as<JsonArray>();
}

void loop()
{
    if (Serial.available() > 0) {
        int mode = Serial.parseInt();
        char flavorChar = readFlavor();
        JsonArray toppingsArray = readToppings();
        String top = toppingsArray.getElement(0);
        switch (mode) {
            case 0:
                chef.make(flavorChar, toppingsArray);
                break;
            case 1:
                break;
            default:
                break;
        }
        delay(1000);
    }
}