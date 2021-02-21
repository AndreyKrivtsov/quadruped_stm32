#include "main.h"

int started = 0;

int i = 0;
int ledValue = 1;
extern "C" void TIM6_IRQHandler(void)
{
    if ((TIM6->SR & TIM_SR_UIF) == TIM_SR_UIF)
    {
        TIM6->SR &= ~TIM_SR_UIF;

        if (!started && i > 1000)
        {
            started = 1;
            uartWrite("System started\r");
        }
        if (started && i > 500)
        {
            i = 0;
            ledValue = !ledValue;
            ledRed(ledValue);
        }
        i++;
    }
}

// *******************

void setup()
{
    init_led();
    init_usart(9600);
    init_tim6();
    init_motors();
}

int state = 0;

int main(void)
{
    setup();
    ledRed(1);

    while (1)
    {
        delay(10);
        if (started)
        {
            std::string str = uartRead();
            if (!str.empty())
            {
                if (str == "m1test")
                {
                    uartWriteLn("Motor 1 test start");
                    // setMotor1Value(50, 100);
                }
                else if (str == "m2test")
                {
                    uartWriteLn("Motor 2 test start");
                }
                else if (str == "m3test")
                {
                    uartWriteLn("Motor 3 test start");
                }

                uartWrite("Command ");
                uartWriteLn(str);
                // ledBlue(1);
            }
        }
    }

    return 0;
}