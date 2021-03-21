#include "motors/motor.h"
#include "motors/MotorA.h"


MotorA motorA;


// exported functions *

void setMotor1Speed(float speed, int torque)
{
    motorA.speed(speed, torque);
}

void setMotor1Angle(float angle, int torque)
{
    motorA.angle(angle);
}

// *********************


void init_motors()
{
    init_timer_motors();
    motorA.init();
}

extern "C" void TIM7_IRQHandler(void)
{
    if ((TIM7->SR & TIM_SR_UIF) == TIM_SR_UIF)
    {
        TIM7->SR &= ~TIM_SR_UIF;
    }
    motorA.loop();
}

void init_timer_motors()
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

    TIM7->PSC = 100; // 10khz / 0.1ms
    TIM7->ARR = 1;  // 2ms
    TIM7->DIER |= TIM_DIER_UIE;
    TIM7->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM7_IRQn);
}