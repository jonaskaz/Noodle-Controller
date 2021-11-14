#include "ButtonController.h"

int ButtonController::verticalButtonControl(Button buttonUp, Button buttonDown)
{
    if (buttonUp.pressed())
    {
        movingUp = true;
        movingDown = false;
    }
    if (buttonUp.released())
    {
        movingUp = false;
    }

    if (buttonDown.pressed())
    {
        movingUp = false;
        movingDown = true;
    }
    if (buttonDown.released())
    {
        movingDown = false;
    }

    return movingUp == true ? 100 : movingDown == true ? 0
                                                       : 50;
}

int ButtonController::horizontalButtonControl(Button buttonLeft, Button buttonRight)
{
    if (buttonLeft.pressed())
    {
        movingLeft = true;
        movingRight = false;
    }
    if (buttonLeft.released())
    {
        movingLeft = false;
    }

    if (buttonRight.pressed())
    {
        movingLeft = false;
        movingRight = true;
    }
    if (buttonRight.released())
    {
        movingRight = false;
    }

    return movingLeft == true ? 100 : movingLeft == true ? 0
                                                         : 50;
}

void ButtonController::auxiliaryButtonControl(Button buttonStart, Button buttonStop)
{
    if (buttonStart.pressed())
    {
        Serial.println("Start Button Pressed");
    }
    if (buttonStart.released())
    {
        Serial.println("Start Button Released");
    }

    if (buttonStop.pressed())
    {
        Serial.println("Stop Button Pressed");
    }
    if (buttonStop.released())
    {
        Serial.println("Stop Button Released");
    }
}
