#ifndef USART_H
#define USART_H

#include "stm32f1xx.h"

void init_usart(uint32_t baudrate);

void put_char(uint8_t byte);
int put_line(const char *string);

#endif