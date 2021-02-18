#include "stm32f1xx.h"

void ledRegister(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // GPIO PA Enable
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // GPIO PB Enable

    GPIOA->CRL &= ~GPIO_CRL_CNF3;   // Сбрасываем биты CNF для бита 3. Режим 00 - Push-Pull
    GPIOA->CRL |= GPIO_CRL_MODE3_0; // Выставляем бит MODE0 для 3 пина. Режим MODE01 = Max Speed 10MHz

    GPIOB->CRH &= ~GPIO_CRH_CNF12;   // Сбрасываем биты CNF для бита 12. Режим 00 - Push-Pull
    GPIOB->CRH |= GPIO_CRH_MODE12_0; // Выставляем бит MODE0 для 12 пина. Режим MODE01 = Max Speed 10MHz
}

void ledBlue(uint8_t value)
{
    if (value)
    {
        GPIOA->BSRR |= GPIO_BSRR_BS3;
    }
    else
    {
        GPIOA->BSRR |= GPIO_BSRR_BR3;
    }
}

void ledRed(uint8_t value)
{
    if (value)
    {
        GPIOB->BSRR |= GPIO_BSRR_BS12;
    }
    else
    {
        GPIOB->BSRR |= GPIO_BSRR_BR12;
    }
}

void ledBluePWMInit() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

    GPIOA->CRL &= ~GPIO_CRL_CNF3;
    GPIOA->CRL |= GPIO_CRL_CNF3_1;

    GPIOA->CRL &= ~GPIO_CRL_MODE3;
    GPIOA->CRL |= GPIO_CRL_MODE3_1;

    TIM5->PSC = 1;
    TIM5->ARR = 255;
    TIM5->CCR4 = 0;
    TIM5->CCER |= TIM_CCER_CC4E;
    TIM5->BDTR |= TIM_BDTR_MOE;
    TIM5->CCMR2 = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
    TIM5->CR1 &= ~TIM_CR1_DIR;
    TIM5->CR1 &= ~TIM_CR1_CMS;
    TIM5->CR1 |= 0x00000001;
}

void ledBluePWM(uint16_t value)
{
    if (TIM5->CR1 != 0x00000001)
    {
        ledBluePWMInit();
    }
    if (TIM5->CR1 == 0x00000001)
    {
        TIM5->CCR4 = value;
    }
}