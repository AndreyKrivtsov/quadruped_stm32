#include "stm32f1xx.h"
#include "motor.h"
#include "tim.h"
#include "gpio.h"

uint8_t isTim1Enable = 0;

void rollMotorPinsRegister()
{
    portAEN();
    portAAltEN();
    portBEN();

    pinsEN();

    tim1En();
    isTim1Enable = 1;
}

void rollMotorA(uint8_t value)
{
    if (isTim1Enable)
        return;
    if (value == 1)
    {
        GPIOA->BSRR = GPIO_BSRR_BS8;
        GPIOB->BSRR = GPIO_BSRR_BR13;
    }
    if (value == -1)
    {
        GPIOB->BSRR = GPIO_BSRR_BS13;
        GPIOA->BSRR = GPIO_BSRR_BR8;
    }
    if (value == 0)
    {
        GPIOB->BSRR = GPIO_BSRR_BR13;
        GPIOA->BSRR = GPIO_BSRR_BR8;
    }
}

void rollMotorB(uint8_t value)
{
    if (isTim1Enable)
        return;
    if (value == 1)
    {
        GPIOA->BSRR = GPIO_BSRR_BS9;
        GPIOB->BSRR = GPIO_BSRR_BR14;
    }
    if (value == -1)
    {
        GPIOB->BSRR = GPIO_BSRR_BS14;
        GPIOA->BSRR = GPIO_BSRR_BR9;
    }
    if (value == 0)
    {
        GPIOB->BSRR = GPIO_BSRR_BR14;
        GPIOA->BSRR = GPIO_BSRR_BR9;
    }
}

void rollMotorC(uint8_t value)
{
    if (isTim1Enable)
        return;
    if (value == 1)
    {
        GPIOA->BSRR = GPIO_BSRR_BS10;
        GPIOB->BSRR = GPIO_BSRR_BR15;
    }
    if (value == -1)
    {
        GPIOB->BSRR = GPIO_BSRR_BS15;
        GPIOA->BSRR = GPIO_BSRR_BR10;
    }
    if (value == 0)
    {
        GPIOB->BSRR = GPIO_BSRR_BR15;
        GPIOA->BSRR = GPIO_BSRR_BR10;
    }
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