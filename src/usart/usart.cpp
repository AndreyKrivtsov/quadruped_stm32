/****************************************************************************\
 File:          usart.cpp
 Date:
 
 Description:
 
 Known bugs/missing features:
 
\****************************************************************************/

#include <stdint.h>
#include "stm32f1xx.h"
#include "usart.h"

/*********************** defines                    *************************/

// usart defines
#define USART_BAUD 9600
#define USART_BUFFER_SIZE 16

/*--------------------------------------------------------------------------*\
 
 Function:      init_usart()
 
 Description:   initialize USART1 
 
 Parameters:    uint32_t baudrate - the baudrate to configure
 Returns:       void
 
\*--------------------------------------------------------------------------*/

void init_usart(uint32_t baudrate)
{
    __enable_irq();

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // включаем тактирование UART1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   // разрешаем тактирование порта GPIOA

    // настройка вывода PA9 (TX1) на режим альтернативной функции с активным выходом
    // Биты CNF = 10, ,биты MODE = X1
    GPIOA->CRH &= (~GPIO_CRH_CNF9_0);
    GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9);

    // настройка вывода PA10 (RX1) на режим входа с подтягивающим резистором
    // Биты CNF = 10, ,биты MODE = 00, ODR = 1
    GPIOA->CRH &= (~GPIO_CRH_CNF10_0);
    GPIOA->CRH |= GPIO_CRH_CNF10_1;
    GPIOA->CRH &= (~(GPIO_CRH_MODE10));
    GPIOA->BSRR |= GPIO_ODR_ODR10;

    uint32_t baud = (uint32_t)(8000000 / baudrate);
    USART1->BRR = baud; // скорость 115200 бод

    USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE; // разрешаем приемник, передатчик и прерывание по приему
    USART1->CR2 = 0;
    USART1->CR3 = 0;

    NVIC_EnableIRQ(USART1_IRQn);

    put_line("Echo mode");
}

/*--------------------------------------------------------------------------*\
 
 Function:      put_char()
 
 Description:   put char in USART data register
 
 Parameters:    uint8_t byte  -   the byte to send out usart
 Returns:       void
 
\*--------------------------------------------------------------------------*/

void put_char(uint8_t byte)
{
    if (byte == '\n')
    {
        put_char('\r');
    }
    USART1->DR = (int)(byte);
    while (!(USART1->SR & USART_SR_TXE))
        ;
}

/*--------------------------------------------------------------------------*\
 
 Function:      put_line()
 
 Description:   outputs passed in string and ends with newline
 
 Parameters:    char * string   - string to output
 Returns:       int             - number of chars output
 
\*--------------------------------------------------------------------------*/

int put_line(const char *string)
{
    int count = 0;

    while (*string)
    {
        put_char(*string);
        string++;
        count++;
    }
    put_char('\n');

    return (count);
}

/*--------------------------------------------------------------------------*\
 
 Function:      USART1_IRQHandler
 
 Description:   USART1 Interrupt service routine
 
 Parameters:    void
 Returns:       void
 
\*--------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif

    void USART1_IRQHandler(void)
    {
        if (USART1->SR & USART_SR_ORE)
        {
            // process overrun error if needed
        }

        //прерывание произошло по приёму
        if (USART1->SR & USART_SR_RXNE)
        {
            uint8_t d = USART1->DR; // получить данное
            USART1->DR = d;         // отослать данное назад
            // Сбрасываем флаг прерывания
            USART1->SR &= ~USART_SR_RXNE;
        }

        //прерывание произошло по завершении передачи
        if (USART1->SR & USART_SR_TC)
        {
            // Сбрасываем флаг прерывания
            // USART1->SR &= ~USART_SR_TC;
        }
    }

#ifdef __cplusplus
}
#endif
