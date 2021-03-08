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
                // std::string length = std::to_string(str.size());
                // usart4WriteLn(length);
                if (str[0] == 'm')
                {
                    usart4Write("Motor ");

                    char motor_number = str[1];
                    std::string motor_value = str.substr(3);

                    if (motor_number == '1')
                    {

                        usart4Write("1 ");

                        if (str[2] == 's')
                        {
                            setMotor1Speed(stoi(motor_value), 100);
                            usart4WriteLn("speed " + motor_value);
                        }

                        if (str[2] == 'a')
                        {
                            setMotor1Angle(stoi(motor_value), 100);
                            usart4WriteLn("angle " + motor_value);
                        }
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