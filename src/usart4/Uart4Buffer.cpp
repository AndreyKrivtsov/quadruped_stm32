#include "usart4/Usart4Buffer.h"

    Usart4Buffer::Usart4Buffer()
    {
        start = 0;
        end = 0;
        ready = 0;
    }

    void Usart4Buffer::push(uint8_t d)
    {
        if (end < USART_RX_BUFFER_LENGTH) {
            rx_buffer[end++] = d;
        }
    }

    uint8_t Usart4Buffer::pop()
    {
        if (!empty())
        {
            return rx_buffer[start++];
        }
        else {
            return 0;
        }
    }

    int Usart4Buffer::length()
    {
        return end - start;
    }

    int Usart4Buffer::empty()
    {
        return start == end;
    }

    void Usart4Buffer::clear()
    {
        start = 0;
        end = 0;
    }

    void Usart4Buffer::setReady(int value)
    {
        ready = value;
    }

    int Usart4Buffer::isReady()
    {
        return ready;
    }