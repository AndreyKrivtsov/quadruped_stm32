#include "stm32f1xx.h"

// create simple define abstractions for heartbeat LED
#define LED_PORT GPIOA
#define LED_CR CRL
#define LED_SET GPIO_BSRR_BS3
#define LED_RESET GPIO_BSRR_BR3
#define LED_PORT_RESET_BITS GPIO_CRL_MODE3 | GPIO_CRL_CNF3
#define LED_PORT_SET_BITS GPIO_CRL_MODE3_1 | GPIO_CRL_MODE3_0
#define LED_CLOCK RCC_APB2ENR_IOPBEN

#define LED_DELAY_MS        150

// heartbeat LED global vars
typedef enum
{
    led_idle = 0, led_on, led_off
} led_state_t;

volatile led_state_t    led_state       = led_idle;
volatile led_state_t    led_state_next  = led_on;
volatile uint16_t       led_delay_count = 0;

void init_led()
{
    RCC->APB2ENR |= LED_CLOCK;                  // enable GPIO clock for LED
    LED_PORT->LED_CR &= ~(LED_PORT_RESET_BITS); // reset pin MODE / CNF
    LED_PORT->LED_CR |= (LED_PORT_SET_BITS);    // MODE: 50Mhz ouput CNF: PP
}

void SysTick_Handler1(void)
{
    // update heartbeat LED delay counter and toggle state when needed
    led_delay_count = ( (led_delay_count + 1) % LED_DELAY_MS );
    if(led_delay_count == 0)
    {
        led_state       = led_state_next;
        led_state_next  = led_idle;
    }
}

void init_systick1(void)
{
    int tick_time = SystemCoreClock/1000;       // Generate interrupt each 1 ms
    SysTick_Config(tick_time);                  // Configure systick timer
}

void led_heartbeat(void)
{
    switch(led_state)
    {
        case led_on:
            led_state       = led_idle;
            led_state_next  = led_off;
            LED_PORT->BSRR  = LED_SET;
            break;
            
        case led_off:
            led_state       = led_idle;
            led_state_next  = led_on;
            LED_PORT->BSRR  = LED_RESET;
            break;
            
        default:
            break;
    }
}


//******************* MY ***************************//

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

void ledBluePWMInit()
{
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