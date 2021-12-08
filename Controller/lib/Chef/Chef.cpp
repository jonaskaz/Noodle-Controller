#include <Chef.h>

void Chef::setup(int* toppingPins, StepMotor step, int flavSpeed){
    Chef::step = step;
    Serial.println("Setting Up");
    toppingServoA.attach(toppingPins[0]);
    toppingServoA.write(0);
    toppingServoB.attach(toppingPins[1]);
    toppingServoB.write(0);
    Serial.println("Servos attached");
    AFMS.begin();
    Serial.println("Motors attached");
    /*
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
    unsigned long lastTime = millis();
    unsigned long dispenseTime = 5000;
    flavorMotors[i]->fullOn();
    while ((millis()-lastTime)<dispenseTime) {
        Serial.println((millis()-lastTime));
        flavorMotors[i]->setSpeed(40);
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
    step.goToB(toppingPosx[i], toppingPosy[i]);
    Serial.println(i);
    for (int pos = 0; pos <= 180; pos += 1) {
        topServos[i].write(pos);
        delay(15);
    }
    Serial.println("done");
}

void Chef::make(char flavor, JsonArray toppings){
    Serial.println("making");
    getFlavor(flavor);
    //getToppings(toppings);
    //step.goToB(10, 0);
    delay(5000);
}

