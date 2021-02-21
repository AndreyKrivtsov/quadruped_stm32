#ifndef USART4_H
#define USART4_H

#include "stm32f1xx.h"
#include <string>

void init_usart4(uint32_t baudrate);
void init_usart4_timer(void);

void usart4Write(std::string str);
void usart4WriteLn(std::string str);
std::string usart4Read(void);

void usart4WriteChar(uint8_t byte);
void usart4Receive(uint8_t d);

#endif