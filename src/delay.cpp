#include "stm32f1xx.h"

void delay(uint32_t msec)
{
    for (uint32_t j = 0; j < 2000UL * msec; j++)
    {
        __NOP();
    }
}

void delay_m(uint32_t mcsec)
{
    for (uint32_t j = 0; j < 2UL * mcsec; j++)
    {
        __NOP();
    }
}