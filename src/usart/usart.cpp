/****************************************************************************\
 File:          usart.cpp
 Date:
 
 Description:
 
 Known bugs/missing features:
 
\****************************************************************************/

#include "usart.h"
#include "UsartBuffer.h"

/*********************** defines                    *************************/

// usart defines
#define USART_BAUD 9600
#define BUFFER_SIZE 16

int timerCounter = 0;

UsartBuffer buffer;

void uartWrite(const char *string, unsigned int length)
{
    for (unsigned int i = 0; i < length - 1; i++)
    {
        usartWriteChar(string[i]);
    }

    usartWriteChar('\r');
}

/*--------------------------------------------------------------------------*\
 
 Function:      uartRead()
 
 Description:   outputs passed in string and ends with newline
 
 Parameters:    char * string   - string to output
 Returns:       int             - number of chars output
 
\*--------------------------------------------------------------------------*/

int uartRead(char *arr)
{
    int counter = 0;

    uartWrite("uartread1", sizeof("uartread1"));

    if (!buffer.isEmptyBuffer() && buffer.isReadyBuffer())
    {
        while (!buffer.isEmptyBuffer())
        {
            arr[timerCounter] = buffer.readBuffer();
            counter++;
        }

        return 1;
    }
    return 0;
}

/*--------------------------------------------------------------------------*\
 
 Function:      init_usart()
 
 Description:   initialize USART1 
 
 Parameters:    uint32_t baudrate - the baudrate to configure
 Returns:       void
 
\*--------------------------------------------------------------------------*/

void init_usart(uint32_t baudrate)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // включаем тактирование UART1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   // разрешаем тактирование порта GPIOA
    GPIOA->CRH &= (~GPIO_CRH_CNF9_0);
    GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9);
    GPIOA->CRH &= (~GPIO_CRH_CNF10_0);
    GPIOA->CRH |= GPIO_CRH_CNF10_1;
    GPIOA->CRH &= (~(GPIO_CRH_MODE10));
    GPIOA->BSRR |= GPIO_ODR_ODR10;

    uint32_t baud = (uint32_t)(8000000 / baudrate);
    USART1->BRR = baud; // скорость 115200 бод

    USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    USART1->CR2 = 0;
    USART1->CR3 = 0;

    NVIC_EnableIRQ(USART1_IRQn);
}

/*--------------------------------------------------------------------------*\
 
 Function:      USART1_IRQHandler
 
 Description:   USART1 Interrupt service routine
 
 Parameters:    void
 Returns:       void
 
\*--------------------------------------------------------------------------*/

extern "C" void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_ORE)
    {
    } // process overrun error if needed

    if (USART1->SR & USART_SR_RXNE) //прерывание произошло по приёму
    {
        init_usart_timer();
        timerCounter = 0;
        uint8_t d = USART1->DR; // получить данное
        buffer.writeBuffer(d);
        buffer.setReadyBuffer(0);
        USART1->SR &= ~USART_SR_RXNE; // Сбрасываем флаг прерывания
    }

    if (USART1->SR & USART_SR_TC) //прерывание произошло по завершении передачи
    {
        // Сбрасываем флаг прерывания
        // USART1->SR &= ~USART_SR_TC;
    }
}

/*--------------------------------------------------------------------------*\
 
 Function:      usartWriteChar()
 
 Description:   put char in USART data register
 
 Parameters:    uint8_t byte  -   the byte to send out usart
 Returns:       void
 
\*--------------------------------------------------------------------------*/

void usartWriteChar(uint8_t byte)
{
    if (byte == '\n')
    {
        usartWriteChar('\r');
    }
    USART1->DR = (int)(byte);
    while (!(USART1->SR & USART_SR_TXE))
        ;
}

void init_usart_timer()
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

    TIM5->PSC = 8000;
    TIM5->ARR = 1;
    TIM5->DIER |= TIM_DIER_UIE;
    TIM5->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM5_IRQn);
}

extern "C" void TIM5_IRQHandler(void)
{
    if ((TIM5->SR & TIM_SR_UIF) == TIM_SR_UIF)
    {
        if (timerCounter < 20)
        {
            timerCounter++;
        }
        else
        {
            if (!buffer.isReadyBuffer())
            {
                buffer.setReadyBuffer(1);
                uartWrite("uart received", sizeof("uart received"));
            }
        }
        TIM5->SR &= ~TIM_SR_UIF;
    }
}