#include "UsartBuffer.h"

    UsartBuffer::UsartBuffer()
    {
    }

    void UsartBuffer::writeBuffer(uint8_t d)
    {
        rx_buffer[bufferLength++] = d;
    }

    uint8_t UsartBuffer::readBuffer()
    {
        if (!isEmptyBuffer())
        {
            return rx_buffer[--bufferLength];
        }
        else {
            return '0';
        }
    }

    int UsartBuffer::isEmptyBuffer()
    {
        return !bufferLength;
    }

    void UsartBuffer::setReadyBuffer(int value)
    {
        readyBuffer = value;
    }

    int UsartBuffer::isReadyBuffer()
    {
        return readyBuffer;
    }