#ifndef USARTBUFFER_H
#define USARTBUFFER_H

#include "stm32f1xx.h"

#pragma once

#define USART_RX_BUFFER_LENGTH 30

class UsartBuffer
{

public:
    uint8_t rx_buffer[USART_RX_BUFFER_LENGTH];
    int start;
    int end;

    UsartBuffer();
    void push(uint8_t);
    uint8_t pop();
    int length();
    int empty();
    void clear();
    int isReady();
    void setReady(int);

private:
    int ready;
};

#endif