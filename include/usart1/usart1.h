#ifndef USART_H
#define USART_H

#include "stm32f1xx.h"
// #include <stdio.h>
#include <string>

void init_usart(uint32_t baudrate);
void init_usart_timer(void);

void uartWrite(std::string str);
void uartWriteLn(std::string str);
std::string uartRead(void);

void usartWriteChar(uint8_t byte);
void usartReceive(uint8_t d);

#endif