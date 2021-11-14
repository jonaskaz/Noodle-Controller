#include <Arduino.h>
#include <Button.h>

class ButtonController
{
    int upButtonPin, downButtonPin, leftButtonPin, rightButtonPin, startButtonPin, stopButtonPin;
    bool movingUp, movingDown, movingLeft, movingRight;

public:
    int verticalButtonControl(Button buttonUp, Button buttonDown);
    int horizontalButtonControl(Button buttonLeft, Button buttonRight);
    void auxiliaryButtonControl(Button buttonStart, Button buttonStop);
};
