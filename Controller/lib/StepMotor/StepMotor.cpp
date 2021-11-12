#include "StepMotor.h"


StepMotor::StepMotor(int motorInterfaceType, const int stepPins[3], const int dirPins[3]){
    stepper1 = AccelStepper(motorInterfaceType, stepPins[0], dirPins[0]);
    stepper2 = AccelStepper(motorInterfaceType, stepPins[1], dirPins[1]);
    stepper3 = AccelStepper(motorInterfaceType, stepPins[2], dirPins[2]);
}

void StepMotor::setup(int maxSpeed, int speed, int accelx, int accely, int startPos[2])
{
    stepper1.setAcceleration(accelx);
    stepper1.setMaxSpeed(maxSpeed);
    stepper1.setSpeed(speed);
    stepper1.setCurrentPosition(startPos[0]);
    stepper2.setAcceleration(accely);
    stepper2.setMaxSpeed(maxSpeed);
    stepper2.setSpeed(speed);
    stepper2.setCurrentPosition(startPos[1]);
    stepper3.setAcceleration(accely);
    stepper3.setMaxSpeed(maxSpeed);
    stepper3.setSpeed(speed);
    stepper3.setCurrentPosition(startPos[1]);
    steppers.addStepper(stepper1);
    steppers.addStepper(stepper2);
    steppers.addStepper(stepper3);
}

void StepMotor::calibrate(int yMaxPin, int xMinPin, int xMaxPin)
{
    ezButton yMaxBut(yMaxPin);
    ezButton xMinBut(xMinPin);
    ezButton xMaxBut(xMaxPin);
    yMaxBut.setDebounceTime(10);
    xMinBut.setDebounceTime(10);
    xMaxBut.setDebounceTime(10);
    yMin = stepper2.currentPosition();
    Serial.println(yMin);
    while (yMaxBut.getStateRaw() == 0) {
        goTo(0, 1000);
    }
    yMax = stepper2.currentPosition();
    stepper2.setCurrentPosition(yMax);
    stepper3.setCurrentPosition(yMax);
    delay(500);
    Serial.println(yMax);
    while (xMinBut.getStateRaw() == 0) {
        stepper1.moveTo(-3000);
        stepper1.run();
    }
    stepper1.setCurrentPosition(0);
    xMin = stepper1.currentPosition();
    delay(500);
    Serial.println(xMin);
    while (xMaxBut.getStateRaw() == 0) {
        stepper1.moveTo(3000);
        stepper1.run();
    }
    delay(500);
    xMax = stepper1.currentPosition();
    stepper1.setCurrentPosition(xMax);
    Serial.println(xMax);
    goToB(0, 0);
}

void StepMotor::goTo(int percentx, int percenty)
{
    long * pos = mapPercentToPos(percentx, percenty);
    stepper1.moveTo(pos[0]);
    stepper2.moveTo(pos[1]);
    stepper3.moveTo(pos[2]);
    stepper1.run();
    stepper2.run();
    stepper3.run();
}

void StepMotor::goToB(int percentx, int percenty)
{   
    goTo(percentx, percenty);
    while (stepper1.run() || stepper2.run() || stepper3.run()) {
        stepper1.run();
        stepper2.run();
        stepper3.run();
    }
}

int * StepMotor::getPos()
{
    return mapPosToPercent(stepper1.currentPosition(), stepper2.currentPosition());
}

long * StepMotor::mapPercentToPos(int percentx, int percenty)
{
    static long positions[3];
    float * steps = getPercentSteps();
    Serial.println(steps[0]);
    positions[0] = steps[0] * percentx;
    positions[1] = steps[1] * percenty;
    positions[2] = steps[1] * percenty;
    return positions;
}

float * StepMotor::getPercentSteps()
{
    int rangex = xMin - xMax;
    int rangey = yMin - yMax;
    float stepx = abs(rangex / 100);
    float stepy = abs(rangey / 100);
    static float steps[2] = {stepx, stepy};
    return steps;
}

int * StepMotor::mapPosToPercent(int posx, int posy)
{
    static int percentages[2];
    float * steps = getPercentSteps();
    percentages[0] = (int) posx/steps[0];
    percentages[1] = (int) posy/steps[1];
    return percentages;
}