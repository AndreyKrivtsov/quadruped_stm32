#ifndef USART_H
#define USART_H

#include "stm32f1xx.h"
#include <string>

void init_usart(uint32_t baudrate);
void init_usart_timer();
void put_char(uint8_t byte);

void uartWrite(const char *string, unsigned int length);
int uartRead(char *arr);

void usartWriteChar(uint8_t byte);

#endif