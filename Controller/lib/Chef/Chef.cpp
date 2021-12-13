#include <Chef.h>

void Chef::setup(int* toppingPins, StepMotor *step, int flavSpeed, int waterPins[2], int motorInterfaceType){
    Chef::step = step;
    toppingServoA.attach(toppingPins[0]);
    toppingServoA.write(0);
    toppingServoB.attach(toppingPins[1]);
    toppingServoB.write(0);
    waterStepper = AccelStepper(motorInterfaceType, waterPins[0], waterPins[1]);
    waterStepper.setAcceleration(300.0);
    waterStepper.setMaxSpeed(400.0);
    waterStepper.setCurrentPosition(0);
    AFMS.begin();
}

int Chef::getIndex(char* array, char target){
    int index = 0;
    for (int i=0; i<4; i++) {
        if (array[i] == target){
            index = i;
            break;
        }
    }
    return index;
}

bool Chef::checkFlavor(char flavor){
    bool found = false;
    for (int i=0; i<4; i++) {
        if (flavors[i] == flavor){
            found=true;
            break;
        }
    }
    return found;
}

void Chef::getFlavor(char flavor){
    int i = getIndex(flavors, flavor);
    step->goToB(flavorPosx[i], flavorPosy[i]);
    unsigned long lastTime = millis();
    unsigned long dispenseTime = 2000;
    flavorMotors[i]->fullOn();
    flavorMotors[i]->setSpeed(40);
    while ((millis()-lastTime)<dispenseTime) {
        flavorMotors[i]->run(FORWARD);
    }
    flavorMotors[i]->fullOff();
}

void Chef::getToppings(JsonArray toppings){
    int size = toppings.size();
    for (int i=0; i<size; i++) {
        char toppingChar[10];
        String top = toppings.getElement(i);
        top.toCharArray(toppingChar, 10);
        getTopping(toppingChar[0]);
        delay(1000);
    }
}

void Chef::getTopping(char topping){
    int i = getIndex(toppings, topping);
    step->goToB(toppingPosx[i], toppingPosy[i]);
    for (int pos = 0; pos <= 180; pos += 1) {
        topServos[i].write(pos);
        delay(15);
    }
}

void Chef:: getWater(){
    step->goToB(50, 0);
    step->goToB(50, 85);
    waterStepper.runToNewPosition(300);
    delay(2300);
    waterStepper.runToNewPosition(0);
    delay(5000);
}

void Chef::make(char flavor, JsonArray toppings){
    getFlavor(flavor);
    //getToppings(toppings);
    getWater();
    step->goToB(50, 0);
    delay(5000);
    Serial.println("Done");
}

