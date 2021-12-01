#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <ezButton.h>


class StepMotor : public MultiStepper
{
public:
    StepMotor() = default;
    StepMotor(int motorInterfaceType, const int stepPins[3], const int dirPins[3]);
    AccelStepper stepper1;
    AccelStepper stepper2;
    AccelStepper stepper3;
    MultiStepper steppers;
    void calibrate(int yMaxPin, int xMinPin, int xMaxPin);
    void goTo(int posx, int posy);
    void goToB(int posx, int posy);
    int * getPos();
    void setup(int maxSpeed, int speed, int accelx, int accely, int startPos[2]);
private:
    int xMax = 2500;
    int yMax = 2500;
    int xMin = 0;
    int yMin = 0;
    void setupHelper(AccelStepper stepper, int maxSpeed, int speed, int accel, int startPos);
    long * mapPercentToPos(int percentx, int percenty);
    int * mapPosToPercent(int posx, int posy);
    float * getPercentSteps();
};
