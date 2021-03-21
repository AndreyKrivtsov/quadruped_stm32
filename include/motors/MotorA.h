#ifndef MOTORA_H
#define MOTORA_H

#include "stm32f1xx.h"
#include "timers/tim1.h"
#include "utils/sin.h"
#include "gpio.h"
#include "led.h"

void rollMotorAPWM(uint16_t value);
void rollMotorBPWM(uint16_t value);
void rollMotorCPWM(uint16_t value);

class MotorA
{
public:
    void init()
    {
        pinsRegister();
    }

    void angle(signed int angle)
    {
        target_angle = angle;
    }

    void speed(int speed, int torque)
    {
        // int min = 0;
        // int max = 100;
        // int targetMax = 512;
        // int pwm = (torque - min) / (max - min) * targetMax;
        // int period = ((speed)-min) / (max - min) * targetMax;
        value = speed;
    }

    void loop()
    {
        if (!pause()) return;
        if (target_angle == current_angle) return;
        if (target_angle > current_angle)
        {
            ledBlue(true);
            stepFwd();
        }
        else if (target_angle < current_angle) {
            ledBlue(false);
            stepBwd();
        }
    }

    void stepFwd()
    {
        stepA++;
        stepB++;
        stepC++;
        current_angle++;

        if (stepA == 119)
        {
            stepA = 0;
            ledBlue(ledState);
            ledState = !ledState;
        }

        if (stepB == 119)
            stepB = 0;
        if (stepC == 119)
            stepC = 0;

        setPwm(stepA, stepB, stepC);
    }

    void stepBwd()
    {
        stepA--;
        stepB--;
        stepC--;
        current_angle--;

        if (stepA == 0)
        {
            stepA = 119;
            ledBlue(ledState);
            ledState = !ledState;
        }

        if (stepB == 0)
            stepB = 119;
        if (stepC == 0)
            stepC = 119;

        setPwm(stepA, stepB, stepC);
    }

    void setPwm(uint8_t a, uint8_t b, uint8_t c) {
        rollMotorAPWM(sinTable[a]);
        rollMotorBPWM(sinTable[b]);
        rollMotorCPWM(sinTable[c]);
    }

private:
    signed int current_angle = 0;
    signed int target_angle = 0;

    uint8_t DEGREE_120 = 40;

    int reset_counter = 0;
    int value = 512;

    uint8_t stepA = 0;
    uint8_t stepB = 40;
    uint8_t stepC = 80;

    bool ledState = false;

    bool pause()
    {
        reset_counter++;
        if (reset_counter > value)
        {
            reset_counter = 0;
            return true;
        }
        return false;
    }

    void pinsRegister()
    {
        portAEN();
        portAAltEN();
        portBEN();
        pinsEN();
        tim1En();
    }
};

#endif