#include <ArduinoJson.h>
#include <StepMotor.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>


class Chef
{
public:
    Chef() = default;
    void setup(int toppingPins[4], StepMotor *step, int flavSpeed, int waterPins[2], int motorInterfaceType);
    StepMotor *step;
    char flavors[4] = {'a', 'b', 'c', 'd'};
    int flavorPosx[4] = {17, 17, 87, 87};
    int flavorPosy[4] = {20, 67, 20, 67};
    char toppings[4] = {'a', 'b', 'c', 'd'};
    int toppingPosx[10] = {25, 40, 55, 70};
    int toppingPosy[10] = {95, 95, 95, 95};
    int waterPos[2] = {95, 95};
    void make(char flavor, JsonArray toppings);
    bool checkFlavor(char flavor);
    void getWater();
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    Adafruit_DCMotor *flavorA = AFMS.getMotor(4);
    Adafruit_DCMotor *flavorB = AFMS.getMotor(2);
    Adafruit_DCMotor *flavorC = AFMS.getMotor(1);
    Adafruit_DCMotor *flavorD = AFMS.getMotor(3);
    Adafruit_DCMotor *flavorMotors[4] = {flavorA, flavorB, flavorC, flavorD};
private:
    int getIndex(char* array, char target);
    void getFlavor(char flavor);
    void getToppings(JsonArray toppings);
    void getTopping(char topping);
    AccelStepper waterStepper;
    Servo toppingServoA;
    Servo toppingServoB;
    Servo toppingServoC;
    Servo toppingServoD;
    Servo topServos[4] = {toppingServoA, toppingServoB, toppingServoC, toppingServoD};
};