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
            usart4WriteLn("System started");
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
    init_usart4(9600);
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
            std::string str = usart4Read();
            if (!str.empty())
            {
                if (str[0] == 'm') {
                    usart4Write("Motor ");

                    if (str[1] == '1') {
                        usart4Write("1 ");
                        int speed = stoi(str.substr(2, 3));
                        setMotor1Value(speed, 100);
                        usart4WriteLn("speed " + str.substr(2, 3));
                    }

                    if (str[1] == '2') {
                        usart4Write("2 ");
                        int speed = stoi(str.substr(2, 3));
                        setMotor1Value(speed, 100);
                        usart4WriteLn("speed " + str.substr(2, 3));
                    }

                    if (str[1] == '3') {
                        usart4Write("3 ");
                        int speed = stoi(str.substr(2, 3));
                        setMotor1Value(speed, 100);
                        usart4WriteLn("speed " + str.substr(2, 3));
                    }
                }

                // usart4Write("Command ");
                // usart4WriteLn(str);
                // ledBlue(1);
            }
        }
    }

    return 0;
}