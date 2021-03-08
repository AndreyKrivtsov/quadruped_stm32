#include "motors/motor.h"

#include "motors/MotorA.h"
#include "sin.h"

#include "led.h"
#include "usart4/usart4.h"

// *** variables ******

int reset_1_counter = 0;
int reset_2_counter = 0;
int reset_3_counter = 0;

int motor_1_value = 512;
int motor_2_value = 512;
int motor_3_value = 512;

int ledState = 0;

// ********************

// *** decrarations ***

void motor1Step();
void motor2Step();
void motor3Step();

// ********************

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
    motorHandler();
}

void motorHandler(void)
{
    motorA.loop();

    if (reset_2_counter > motor_2_value)
    {
        motor2Step();
        reset_2_counter = 0;
    }
    reset_2_counter++;

    if (reset_3_counter > motor_3_value)
    {
        motor3Step();
        reset_3_counter = 0;
    }
    reset_3_counter++;
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


// **************************************************

// *************** motor 2 step *********************

void motor2Step()
{
}


// **************************************************

// *************** motor 2 step *********************

void motor3Step()
{
}

// **************************************************