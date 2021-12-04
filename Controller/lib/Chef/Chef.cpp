#include <Chef.h>

void Chef::setup(int* flavorPins, int* toppingPins, StepMotor step, float flavSpeed){
    Chef::step = step;
    /*
    Serial.begin(115200);
    toppingServoA.attach(toppingPins[0]);
    toppingServoB.attach(toppingPins[1]);
    toppingServoC.attach(toppingPins[2]);
    toppingServoD.attach(toppingPins[3]);
    flavorA = AFMS.getMotor(flavorPins[0]);
    flavorB = AFMS.getMotor(flavorPins[1]);
    flavorC = AFMS.getMotor(flavorPins[2]);
    flavorD = AFMS.getMotor(flavorPins[3]);
    flavorA->setSpeed(flavSpeed);
    flavorB->setSpeed(flavSpeed);
    flavorC->setSpeed(flavSpeed);
    flavorD->setSpeed(flavSpeed);
    AFMS.begin();
    */
    
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

void Chef::getFlavor(char flavor){
    int i = getIndex(flavors, flavor);
    step.goToB(flavorPosx[i], flavorPosy[i]);
    unsigned long currTime = millis();
    unsigned long dispenseTime = 5000;
    while ((millis()-currTime)<dispenseTime) {
        //flavorMotors[i]->run(FORWARD);
        ;
    }
}

void Chef::getToppings(JsonArray toppings){
    int size = toppings.size();
    for (int i=0; i<size; i++) {
        char toppingChar[5];
        String top = toppings.getElement(i);
        top.toCharArray(toppingChar, 5);
        getTopping(toppingChar[0]);
        delay(1000);
    }
}

void Chef::getTopping(char topping){
    int i = getIndex(toppings, topping);
    step.goToB(toppingPosx[i], toppingPosy[i]);
    for (int pos = 0; pos <= 180; pos += 1) {
        //topServos[i].write(pos);
        delay(15);
    }
}

void Chef::make(char flavor, JsonArray toppings){
    getFlavor(flavor);
    getToppings(toppings);
    step.goToB(10, 0);
    delay(5000);
}

