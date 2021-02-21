/****************************************************************************\
 File:          usart.cpp
 Date:
 
 Description:
 
 Known bugs/missing features:
 
\****************************************************************************/

#include "usart4/usart4.h"
#include "usart4/Usart4Buffer.h"

/*********************** defines                    *************************/

// usart defines
#define USART_BAUD 9600
#define BUFFER_SIZE 16

int is_uart4_init = 0;
int timerCounter4 = 0;

Usart4Buffer buffer4;

void printUsart4State();

void usart4Write(std::string str)
{
    for (unsigned int i = 0; i < str.length(); i++)
    {
        usart4WriteChar((char)str[i]);
    }
}

void usart4WriteLn(std::string str)
{
    usart4Write(str);
    usart4WriteChar('\r');
}

/*--------------------------------------------------------------------------*\
 
 Function:      uartRead()
 
 Description:   outputs passed in string and ends with newline
 
 Parameters:    char * string   - string to output
 Returns:       int             - number of chars output
 
\*--------------------------------------------------------------------------*/

std::string usart4Read()
{
    if (!buffer4.empty() && buffer4.isReady())
    {
        std::string str;
        
        while (!buffer4.empty())
        {
            str += buffer4.pop();
        }

        buffer4.clear();
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

void init_usart4(uint32_t baudrate)
{
    RCC->APB1ENR |= RCC_APB1ENR_UART4EN; // включаем тактирование UART1
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;   // разрешаем тактирование порта GPIOA
    GPIOC->CRH &= (~GPIO_CRH_CNF10_0);
    GPIOC->CRH |= (GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10);
    GPIOC->CRH &= (~GPIO_CRH_CNF11_0);
    GPIOC->CRH |= GPIO_CRH_CNF11_1;
    GPIOC->CRH &= (~(GPIO_CRH_MODE11));
    GPIOC->BSRR |= GPIO_ODR_ODR11;

    uint32_t baud = (uint32_t)(8000000 / baudrate);
    UART4->BRR = baud;

    UART4->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE;
    UART4->CR2 = 0;
    UART4->CR3 = 0;

    NVIC_EnableIRQ(UART4_IRQn);
}

/*--------------------------------------------------------------------------*\
 
 Function:      USART1_IRQHandler
 
 Description:   USART1 Interrupt service routine
 
 Parameters:    void
 Returns:       void
 
\*--------------------------------------------------------------------------*/

extern "C" void UART4_IRQHandler(void)
{
    if (UART4->SR & USART_SR_ORE)
    {
    }
    if (UART4->SR & USART_SR_RXNE)
    {
        init_usart4_timer();
        uint8_t d = UART4->DR;
        usart4Receive(d);

        UART4->SR &= ~USART_SR_RXNE;
    }
    if (UART4->SR & USART_SR_TC)
    {
        UART4->SR &= ~USART_SR_TC;
    }
}

void usart4Receive(uint8_t d)
{
    timerCounter4 = 0;

    if (buffer4.isReady())
    {
        buffer4.clear();
        buffer4.setReady(0);
    }

    buffer4.push(d);
}

/*--------------------------------------------------------------------------*\
 
 Function:      usartWriteChar()
 
 Description:   put char in USART data register
 
 Parameters:    uint8_t byte  -   the byte to send out usart
 Returns:       void
 
\*--------------------------------------------------------------------------*/

void usart4WriteChar(uint8_t byte)
{
    if (byte == '\n')
    {
        usart4WriteChar('\r');
    }
    UART4->DR = (int)(byte);
    while (!(UART4->SR & USART_SR_TXE))
        ;
}

void init_usart4_timer()
{
    if (!is_uart4_init)
    {
        is_uart4_init = 1;
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
        if (timerCounter4 < 20)
        {
            timerCounter4++;
        }
        else
        {
            timerCounter4 = 0;

            if (!buffer4.isReady())
            {
                buffer4.setReady(1);
            }
        }
        TIM5->SR &= ~TIM_SR_UIF;
    }
}

void printUsart4State()
{
    usart4Write("l ");
    usart4WriteChar(buffer4.length() + 48);
    usart4Write(" ");

    usart4Write("; val ");
    int l = buffer4.length();

    for (int i = 0; i < l; i++)
    {
        const char asd = buffer4.pop();
        usart4WriteChar(asd);
    }

    usart4Write("\r");
    buffer4.clear();
}