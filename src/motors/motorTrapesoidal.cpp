// *************************

// A+ B- C0
// A+ B0 C-
// A0 B+ C-
// A- B+ C0
// A- B0 C+
// A0 B- C+

// void trapesoidal()
// {
//     uint16_t speed = 1000;

//     while (1)
//     {
//         rollMotorA(1);
//         rollMotorB(-1);
//         rollMotorC(0);
//         ledRed(1);
//         ledBlue(0);
//         delay(speed);

//         rollMotorA(1);
//         rollMotorB(0);
//         rollMotorC(-1);
//         ledRed(0);
//         ledBlue(1);
//         delay(speed);

//         rollMotorA(0);
//         rollMotorB(1);
//         rollMotorC(-1);
//         ledBlue(0);
//         delay(speed);

//         rollMotorA(-1);
//         rollMotorB(1);
//         rollMotorC(0);
//         ledRed(1);
//         ledBlue(0);
//         delay(speed);

//         rollMotorA(-1);
//         rollMotorB(0);
//         rollMotorC(1);
//         ledRed(0);
//         ledBlue(1);
//         delay(speed);

//         rollMotorA(0);
//         rollMotorB(-1);
//         rollMotorC(1);
//         ledBlue(0);
//         delay(speed);
//     }
// }


// void rollMotorA(uint8_t value)
// {
//     if (isTim1Enable)
//         return;
//     if (value == 1)
//     {
//         GPIOA->BSRR = GPIO_BSRR_BS8;
//         GPIOB->BSRR = GPIO_BSRR_BR13;
//     }
//     if (value == -1)
//     {
//         GPIOB->BSRR = GPIO_BSRR_BS13;
//         GPIOA->BSRR = GPIO_BSRR_BR8;
//     }
//     if (value == 0)
//     {
//         GPIOB->BSRR = GPIO_BSRR_BR13;
//         GPIOA->BSRR = GPIO_BSRR_BR8;
//     }
// }

// void rollMotorB(uint8_t value)
// {
//     if (isTim1Enable)
//         return;
//     if (value == 1)
//     {
//         GPIOA->BSRR = GPIO_BSRR_BS9;
//         GPIOB->BSRR = GPIO_BSRR_BR14;
//     }
//     if (value == -1)
//     {
//         GPIOB->BSRR = GPIO_BSRR_BS14;
//         GPIOA->BSRR = GPIO_BSRR_BR9;
//     }
//     if (value == 0)
//     {
//         GPIOB->BSRR = GPIO_BSRR_BR14;
//         GPIOA->BSRR = GPIO_BSRR_BR9;
//     }
// }

// void rollMotorC(uint8_t value)
// {
//     if (isTim1Enable)
//         return;
//     if (value == 1)
//     {
//         GPIOA->BSRR = GPIO_BSRR_BS10;
//         GPIOB->BSRR = GPIO_BSRR_BR15;
//     }
//     if (value == -1)
//     {
//         GPIOB->BSRR = GPIO_BSRR_BS15;
//         GPIOA->BSRR = GPIO_BSRR_BR10;
//     }
//     if (value == 0)
//     {
//         GPIOB->BSRR = GPIO_BSRR_BR15;
//         GPIOA->BSRR = GPIO_BSRR_BR10;
//     }
// }