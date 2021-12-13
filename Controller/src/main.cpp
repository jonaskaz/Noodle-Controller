#include <Arduino.h>
#include <Chef.h>
#include <ArduinoJson.h>

#define yMaxPin 8
#define xMaxPin 12
#define xMinPin 9
#define motorInterfaceType 1

const int stepPins[3] =  {3, 5, 7};
const int dirPins[3] = {2, 4, 6};
int toppingPins[4] = {22, 24, 11, 11};
int waterPins[2] = {46, 47};


StepMotor step = StepMotor(motorInterfaceType, stepPins, dirPins);
Chef chef = Chef();
StaticJsonDocument<200> doc;
int numOrders = 0;

void setup()
{
    Serial.begin(115200);
    int startingPos[2] = {0,0};
    step.setup(1000, 700, 1000, 1000, startingPos);
    StepMotor* stepPtr = &step;
    chef.setup(toppingPins, stepPtr, 20, waterPins, motorInterfaceType);
    delay(3000);
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
    if (Serial.available() > 5) {
        int mode = Serial.parseInt();
        char flavorChar = readFlavor();
        JsonArray toppingsArray = readToppings();
        String top = toppingsArray.getElement(0);
        if (chef.checkFlavor(flavorChar)){
            numOrders+=1;
            if (numOrders%3 == 0){
                step.calibrate(yMaxPin, xMinPin, xMaxPin);
            }
            switch (mode) {
                case 0:
                    chef.make(flavorChar, toppingsArray);
                    break;
                case 1:
                    break;
                default:
                    break;
            }
        }
        delay(3000);
    }
}