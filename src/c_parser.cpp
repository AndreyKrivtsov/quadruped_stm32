#include "c_parser.h"

void c_parse(std::string str, int argv[])
{
    if (str[0] == 'm')
    {
        argv[0] = 0;
    }
    else if (str[0] == 'a')
    {
    }

    if (str[1] == '1')
    {
        argv[1] = 0;
    }
    // else if (str[1] == '2')
    // {
    //     argv[1] = 1;
    // }
    // else if (str[1] == '3')
    // {
    //     argv[1] = 2;
    // }
}

// usart4Write("1 ");
// int speed = stoi(str.substr(2, 3));
// setMotor1Value(speed, 100);
// usart4WriteLn("speed " + str.substr(2, 3));