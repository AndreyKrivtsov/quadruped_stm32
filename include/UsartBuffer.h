#ifndef USARTBUFFER_H
#define USARTBUFFER_H

#include "stm32f1xx.h"

#pragma once

#define USART_RX_BUFFER_LENGTH 30

class UsartBuffer
{

public:
    uint8_t rx_buffer[USART_RX_BUFFER_LENGTH];

    UsartBuffer();
    void writeBuffer(uint8_t);
    uint8_t readBuffer();
    int isEmptyBuffer();
    int isReadyBuffer();
    void setReadyBuffer(int);

private:
    int bufferLength;
    int readyBuffer;
};

#endif