#include "motors/MotorA.h"

void rollMotorAPWM(uint16_t value)
{
    TIM1->CCR1 = value;
}

void rollMotorBPWM(uint16_t value)
{
    TIM1->CCR2 = value;
}

void rollMotorCPWM(uint16_t value)
{
    TIM1->CCR3 = value;
}