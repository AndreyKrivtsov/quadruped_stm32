/****************************************************************************\
 File:          usart.cpp
 Date:
 
 Description:
 
 Known bugs/missing features:
 
\****************************************************************************/

#include "usart1/usart1.h"
#include "usart1/UsartBuffer.h"

/*********************** defines                    *************************/

// usart defines
#define USART_BAUD 9600
#define BUFFER_SIZE 16

int is_usart_init = 0;
int timerCounter = 0;

UsartBuffer buffer;

void printUsartState();

void uartWrite(std::string str)
{
    for (unsigned int i = 0; i < str.length(); i++)
    {
        usartWriteChar((char)str[i]);
    }
}

void uartWriteLn(std::string str)
{
    uartWrite(str);
    usartWriteChar('\r');
}

/*--------------------------------------------------------------------------*\
 
 Function:      uartRead()
 
 Description:   outputs passed in string and ends with newline
 
 Parameters:    char * string   - string to output
 Returns:       int             - number of chars output
 
\*--------------------------------------------------------------------------*/

std::string uartRead()
{
    if (!buffer.empty() && buffer.isReady())
    {
        std::string str;
        
        while (!buffer.empty())
        {
            str += buffer.pop();
        }

        buffer.clear();
        return str;
    }
    return "";
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
    }
    if (USART1->SR & USART_SR_RXNE)
    {
        init_usart_timer();
        uint8_t d = USART1->DR;
        usartReceive(d);

        USART1->SR &= ~USART_SR_RXNE;
    }
    if (USART1->SR & USART_SR_TC)
    {
        USART1->SR &= ~USART_SR_TC;
    }
}

void usartReceive(uint8_t d)
{
    timerCounter = 0;

    if (buffer.isReady())
    {
        buffer.clear();
        buffer.setReady(0);
    }

    buffer.push(d);
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
    if (!is_usart_init)
    {
        is_usart_init = 1;
        RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
        TIM5->PSC = 8000;
        TIM5->ARR = 1;
        TIM5->DIER |= TIM_DIER_UIE;
        TIM5->CR1 |= TIM_CR1_CEN;
        NVIC_EnableIRQ(TIM5_IRQn);
    }
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
            timerCounter = 0;

            if (!buffer.isReady())
            {
                buffer.setReady(1);
            }
        }
        TIM5->SR &= ~TIM_SR_UIF;
    }
}

void printUsartState()
{
    uartWrite("l ");
    usartWriteChar(buffer.length() + 48);
    uartWrite(" ");

    uartWrite("; val ");
    int l = buffer.length();

    for (int i = 0; i < l; i++)
    {
        const char asd = buffer.pop();
        usartWriteChar(asd);
    }

    uartWrite("\r");
    buffer.clear();
}