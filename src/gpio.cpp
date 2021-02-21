#include "stm32f1xx.h"
#include "gpio.h"

void portAEN()
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // IO PA Enable
}

void portAAltEN()
{
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}

void portBEN()
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // IO PB Enable
}

void pinsEN() {
    pinPA8EN();
    pinPA9EN();
    pinPA10EN();
    pinPB13EN();
    pinPB14EN();
    pinPB15EN();
}

void pinPA8EN()
{
    GPIOA->CRH &= ~GPIO_CRH_CNF8;
    GPIOA->CRH |= GPIO_CRH_CNF8_1;

    GPIOA->CRH &= ~GPIO_CRH_MODE8;
    GPIOA->CRH |= GPIO_CRH_MODE8_0;
}

void pinPA9EN()
{
    GPIOA->CRH &= ~GPIO_CRH_CNF9;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;

    GPIOA->CRH &= ~GPIO_CRH_MODE9;
    GPIOA->CRH |= GPIO_CRH_MODE9_0;
}

void pinPA10EN()
{
    GPIOA->CRH &= ~GPIO_CRH_CNF10;
    GPIOA->CRH |= GPIO_CRH_CNF10_1;

    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH |= GPIO_CRH_MODE10_0;
}

void pinPB13EN()
{
    GPIOB->CRH &= ~GPIO_CRH_CNF13;
    GPIOB->CRH |= GPIO_CRH_CNF13_1;
    GPIOB->CRH |= GPIO_CRH_MODE13_0;
}

void pinPB14EN()
{
    GPIOB->CRH &= ~GPIO_CRH_CNF14;
    GPIOB->CRH |= GPIO_CRH_CNF14_1;
    GPIOB->CRH |= GPIO_CRH_MODE14_0;
}

void pinPB15EN()
{
    GPIOB->CRH &= ~GPIO_CRH_CNF15;
    GPIOB->CRH |= GPIO_CRH_CNF15_1;
    GPIOB->CRH |= GPIO_CRH_MODE15_0;
}