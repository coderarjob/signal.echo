#include <avr/io.h>
#include <main.h>

static void wait_transmit_complete()
{
    while ((UCSRA & (1 << UDRE)) == 0)
        ;
}

void usart_on()
{
    UBRRH = 0;    // HIGH8(BAUD_COUNTER);
    UBRRL = 0x4A; // LOW8(BAUD_COUNTER);

    BIT_SET_MASK(UCSRC, (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0) | (1 << USBS));
    BIT_SET_MASK(UCSRB, (1 << TXEN));
}

void usart_off()
{
    wait_transmit_complete();
    BIT_CLEAR_MASK(UCSRB, (1 << TXEN));
}

void usart_send_string (const char* str)
{
    char c;
    while ((c = *str++)) {
        usart_send_char (c);
    }
}

void usart_send_char (char c)
{
    wait_transmit_complete();
    UDR = c;
}
