#include <motor_driver.h>
#include <Arduino.h>

/**
 * Low level motor driver specific implementation
 */
class bts7960drv : public MotorDrv
{
public:
    int pinL, pinR;
    int pwmChanL, pwmChanR;

    bts7960drv(int pinR, int pinL, int pwmChL, int pwmChR) : pinL(pinL), pinR(pinR), pwmChanL(pwmChL), pwmChanR(pwmChR)
    {
        // configure LED PWM functionalitites
        ledcSetup(pwmChanR, pwmFreq, pwmRes);
        ledcSetup(pwmChanL, pwmFreq, pwmRes);

        // attach the channel to the GPIO to be controlled
        ledcAttachPin(pinR, pwmChanR);
        ledcAttachPin(pinL, pwmChanL);
    }

    void driveMotor(int dutyCycle, bool direction) override
    {
        // move forward
        if (direction)
        {
            ledcWrite(pwmChanL, 0);
            ledcWrite(pwmChanR, dutyCycle);
        }
        // move backward
        else
        {
            ledcWrite(pwmChanL, dutyCycle);
            ledcWrite(pwmChanR, 0);
        }
    }

    void enable(bool isEnabled) override
    {
    }
};
