#include <ArduinoJson.h>
#include <StepMotor.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>


class Chef
{
public:
    Chef() = default;
    void setup(int flavorPins[4], int toppingPins[4], StepMotor step, float flavSpeed);
    StepMotor step;
    char flavors[4] = "abcd";
    int flavorPosx[4] = {25, 25, 75, 75};
    int flavorPosy[4] = {25, 75, 25, 75};
    char toppings[4] = "abcd";
    int toppingPosx[10] = {25, 40, 55, 70};
    int toppingPosy[10] = {95, 95, 95, 95};
    int waterPos[2] = {95, 95};
    void make(char flavor, JsonArray toppings);
private:
    int getIndex(char* array, char target);
    void getFlavor(char flavor);
    void getToppings(JsonArray toppings);
    void getTopping(char topping);
    Servo toppingServoA;
    Servo toppingServoB;
    Servo toppingServoC;
    Servo toppingServoD;
    Servo topServos[4] = {toppingServoA, toppingServoB, toppingServoC, toppingServoD};
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    Adafruit_DCMotor *flavorA;
    Adafruit_DCMotor *flavorB;
    Adafruit_DCMotor *flavorC;
    Adafruit_DCMotor *flavorD;
    Adafruit_DCMotor *flavorMotors[4] = {flavorA, flavorB, flavorC, flavorD};
};