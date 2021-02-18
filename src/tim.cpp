#include "stm32f1xx.h"
#include "tim.h"

void tim1En(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    // входной предварительный делитель частоты
    TIM1->PSC = 0;
    // регистр автоматической перезагрузки
    TIM1->ARR = 512;
    // коэф. заполнения
    TIM1->CCR1 = 0;

    tim1ConfCh1();
    tim1ConfCh2();
    tim1ConfCh3();

    //разрешим использовать выводы таймера как выходы
    TIM1->BDTR |= TIM_BDTR_MOE | 50;
    //считаем вверх
    TIM1->CR1 &= ~TIM_CR1_DIR;
    //выравнивание по фронту, Fast PWM
    TIM1->CR1 &= ~TIM_CR1_CMS;
    //включаем счётчик
    // TIM1->CR1 |= TIM_CR1_CEN;
    TIM1->CR1 |= 0x00000001;
}

void tim1ConfCh1(void)
{
    // на выход канал 1, активный уровень низкий
    TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC1NE;
    //PWM mode 1, прямой ШИМ 1 канал
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
}

void tim1ConfCh2()
{
    // на выход канал 2, активный уровень низкий
    TIM1->CCER |= TIM_CCER_CC2E | TIM_CCER_CC2NE;
    //PWM mode 1, прямой ШИМ 2 канал
    TIM1->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
}

void tim1ConfCh3()
{
    // на выход канал 3, активный уровень низкий
    TIM1->CCER |= TIM_CCER_CC3E | TIM_CCER_CC3NE;
    //PWM mode 1, прямой ШИМ 3 канал
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
}