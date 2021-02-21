#include "usart1/UsartBuffer.h"

    UsartBuffer::UsartBuffer()
    {
        start = 0;
        end = 0;
        ready = 0;
    }

    void UsartBuffer::push(uint8_t d)
    {
        if (end < USART_RX_BUFFER_LENGTH) {
            rx_buffer[end++] = d;
        }
    }

    uint8_t UsartBuffer::pop()
    {
        if (!empty())
        {
            return rx_buffer[start++];
        }
        else {
            return 0;
        }
    }

    int UsartBuffer::length()
    {
        return end - start;
    }

    int UsartBuffer::empty()
    {
        return start == end;
    }

    void UsartBuffer::clear()
    {
        start = 0;
        end = 0;
    }

    void UsartBuffer::setReady(int value)
    {
        ready = value;
    }

    int UsartBuffer::isReady()
    {
        return ready;
    }