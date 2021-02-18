#include "stm32f1xx.h"
#include "stdio.h"

#include "motor.h"
#include "led.h"
#include "delay.h"

void trapesoidal();

// A+ B- C0
// A+ B0 C-
// A0 B+ C-
// A- B+ C0
// A- B0 C+
// A0 B- C+

uint16_t sinTable[120] = {
    0, 0, 1, 3, 6, 9, 13, 17, 22, 28, 34, 41, 49, 57, 66, 75, 85, 95, 106, 117, 128, 140, 152, 164, 177, 190, 203, 216, 229, 243, 256, 269, 283, 296, 309, 322, 335, 348, 360, 372, 384, 395, 406, 417, 427, 437, 446, 455, 463, 471, 478, 484, 490, 495, 499, 503, 506, 509, 511, 512, 512, 512, 511, 509, 506, 503, 499, 495, 490, 484, 478, 471, 463, 455, 446, 437, 427, 417, 406, 395, 384, 372, 360, 348, 335, 322, 309, 296, 283, 269, 256, 243, 229, 216, 203, 190, 177, 164, 152, 140, 128, 117, 106, 95, 85, 75, 66, 57, 49, 41, 34, 28, 22, 17, 13, 9, 6, 3, 1, 0
};

uint8_t pwmSin[48] = {
    127, 110, 94, 78, 64, 50, 37, 26, 17, 10,
    4, 1, 0, 1, 4, 10, 17, 26, 37, 50,
    64, 78, 94, 110, 127, 144, 160, 176, 191, 204,
    217, 228, 237, 244, 250, 253, 255, 253, 250, 244,
    237, 228, 217, 204, 191, 176, 160, 144};

uint16_t currentStepA = 0;
uint16_t currentStepB = 40;
uint16_t currentStepC = 80;
uint8_t pos;

void setup()
{
    ledRegister();
    rollMotorPinsRegister();
}

int speed = 10000;
uint8_t round = 1;
uint8_t loopCount = 0;

int main(void)
{
    setup();

    while (1)
    {
        ledBluePWM(sinTable[currentStepA]);

        rollMotorAPWM(sinTable[currentStepA]);
        rollMotorBPWM(sinTable[currentStepB]);
        rollMotorCPWM(sinTable[currentStepC]);

        currentStepA++;
        currentStepB++;
        currentStepC++;

        if (currentStepA == 119)
            currentStepA = 0;
        if (currentStepB == 119)
            currentStepB = 0;
        if (currentStepC == 119)
            currentStepC = 0;

        delayMc(speed);

        if (currentStepA == 0){
            loopCount++;
        }

        if (loopCount == round)
        {
            speed /= 2;
            round *= 2;
            loopCount = 0;
        }

        if (speed < 100)
        {
            speed = 10000;
            round = 1;
        }
    }

    return 0;
}

void trapesoidal()
{
    uint16_t speed = 1000;

    while (1)
    {
        rollMotorA(1);
        rollMotorB(-1);
        rollMotorC(0);
        ledRed(1);
        ledBlue(0);
        delay(speed);

        rollMotorA(1);
        rollMotorB(0);
        rollMotorC(-1);
        ledRed(0);
        ledBlue(1);
        delay(speed);

        rollMotorA(0);
        rollMotorB(1);
        rollMotorC(-1);
        ledBlue(0);
        delay(speed);

        rollMotorA(-1);
        rollMotorB(1);
        rollMotorC(0);
        ledRed(1);
        ledBlue(0);
        delay(speed);

        rollMotorA(-1);
        rollMotorB(0);
        rollMotorC(1);
        ledRed(0);
        ledBlue(1);
        delay(speed);

        rollMotorA(0);
        rollMotorB(-1);
        rollMotorC(1);
        ledBlue(0);
        delay(speed);
    }
}