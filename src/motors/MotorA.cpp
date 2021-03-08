#include "motors/MotorA.h"

void rollMotorPinsRegister()
{
    portAEN();
    portAAltEN();
    portBEN();
    pinsEN();
    tim1En();
}

void rollMotorAPWM(uint16_t value)
{
    rollMotorPinAP(value);
}

void rollMotorBPWM(uint16_t value)
{
    rollMotorPinBP(value);
}

void rollMotorCPWM(uint16_t value)
{
    rollMotorPinCP(value);
}

void rollMotorPinAP(uint16_t value)
{
    TIM1->CCR1 = value;
}

void rollMotorPinBP(uint16_t value)
{
    TIM1->CCR2 = value;
}

void rollMotorPinCP(uint16_t value)
{
    TIM1->CCR3 = value;
}