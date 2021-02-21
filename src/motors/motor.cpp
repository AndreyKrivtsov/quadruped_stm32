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

// exported functions *

void setMotor1Value(float speed, int torque)
{
    int min = 0;
    int max = 100;
    int targetMax = 512;
    int pwm = (torque - min) / (max - min) * targetMax;
    int period = ((speed)-min) / (max - min) * targetMax;
    // usart4WriteLn(std::to_string((int)period));
    // motor_1_value = (int)period;
    motor_1_value = speed;
}

// *********************

void init_motors()
{
    init_timer_motors();
    rollMotorPinsRegister();
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
    if (reset_1_counter > motor_1_value)
    {
        motor1Step();
        reset_1_counter = 0;
    }
    reset_1_counter++;

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

// *************** motor 1 step *********************

uint16_t currentMotor1StepA = 0;
uint16_t currentMotor1StepB = 40;
uint16_t currentMotor1StepC = 80;

void motor1Step()
{
    // usart4Write(std::to_string((int)currentMotor1StepA) + " | ");
    // usart4Write(std::to_string((int)currentMotor1StepB) + " | ");
    // usart4WriteLn(std::to_string((int)currentMotor1StepC));

    if (currentMotor1StepA == 119)
    {
        currentMotor1StepA = 0;
        ledBlue(ledState);
        ledState = !ledState;
    }

    if (currentMotor1StepB == 119)
        currentMotor1StepB = 0;
    if (currentMotor1StepC == 119)
        currentMotor1StepC = 0;

    rollMotorAPWM(sinTable[currentMotor1StepA]);
    rollMotorBPWM(sinTable[currentMotor1StepB]);
    rollMotorCPWM(sinTable[currentMotor1StepC]);

    currentMotor1StepA++;
    currentMotor1StepB++;
    currentMotor1StepC++;
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