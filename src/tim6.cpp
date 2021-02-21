#include "tim6.h"

void init_tim6()
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    TIM6->PSC = 1000;
    TIM6->ARR = 8;
    TIM6->DIER |= TIM_DIER_UIE;
    TIM6->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM6_IRQn);
}