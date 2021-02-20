#include "main.h"

#include "motors/motor.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "tim6.h"

// *** test timer ***

int ledValue = 1;
extern "C" void TIM6_IRQHandler(void)
{
    if ((TIM6->SR & TIM_SR_UIF) == TIM_SR_UIF)
    {
        TIM6->SR &= ~TIM_SR_UIF;
        ledValue = !ledValue;
        ledRed(ledValue);
        ledBlue(ledValue);

        // uartWrite("LED BLINK", sizeof("LED BLINK"));
    }
}

// *******************

void setup()
{
    init_motors();
    init_tim6();
    init_led();
    init_usart(9600);
    // setMotor1Value(50, 100);
}

int main(void)
{
    setup();

    uartWrite("command1", sizeof("command1"));

    while (1)
    {
        // step for all motors
        // motorHandler();

        char command[30];
        uartRead(command);
        if (uartRead(command))
        {
            uartWrite("command", sizeof("command"));
            usartWriteChar(command[0]);
        }

        // delayMc(100);
    }

    return 0;
}