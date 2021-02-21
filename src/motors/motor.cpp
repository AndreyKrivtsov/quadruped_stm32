#include "motors/motor.h"

#include "motors/MotorA.h"
#include "sin.h"

#include "led.h"

// *** constants ******

int reset_1_counter = 0;
int reset_2_counter = 0;
int reset_3_counter = 0;

int motor_1_value = 512;
int motor_2_value = 512;
int motor_3_value = 512;

// ********************

// *** decrarations ***

void motor1Step();
void motor2Step();
void motor3Step();

// ********************

// exported functions *

void setMotor1Value(int speed, int torque)
{
    int min = 0;
    int max = 100;
    int targetMax = 512;
    int pwm = (torque - min) / (max - min) * targetMax;
    int period = (speed - min) / (max - min) * targetMax;
}

// *********************

void init_motors()
{
    init_timer_motors();
    rollMotorPinsRegister();
}

int ledState = 0;
extern "C" void TIM7_IRQHandler(void)
{
    if ((TIM7->SR & TIM_SR_UIF) == TIM_SR_UIF)
    {
        TIM7->SR &= ~TIM_SR_UIF;
    }
    ledBlue(ledState);
    ledState = !ledState;
    // motorHandler();
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

    TIM7->PSC = 8000; // 1khz / 1ms
    TIM7->ARR = 100; // 100ms
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
    rollMotorAPWM(sinTable[currentMotor1StepA]);
    rollMotorBPWM(sinTable[currentMotor1StepB]);
    rollMotorCPWM(sinTable[currentMotor1StepC]);

    currentMotor1StepA++;
    currentMotor1StepB++;
    currentMotor1StepC++;

    if (currentMotor1StepA == 119)
        currentMotor1StepA = 0;
    if (currentMotor1StepB == 119)
        currentMotor1StepB = 0;
    if (currentMotor1StepC == 119)
        currentMotor1StepC = 0;
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