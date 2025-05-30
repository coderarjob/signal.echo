#pragma once

#define BAUD         10000
#define BAUD_COUNTER (((unsigned int)F_CPU / (16 * BAUD)) - 1)

#define HIGH8(v)     ((v >> 8) & 0xFF)
#define LOW8(v)      (v & 0xFF)

#define BIT_CLEAR_MASK(port, mask)  ((port) &= ~(mask))
#define BIT_SET_MASK(port, mask)    ((port) |= (mask))
#define IS_BIT_SET_MASK(port, mask) ((port) &= (mask))

#define BIT_CLEAR(port, pin)        BIT_CLEAR_MASK (port, 1 << (pin))
#define BIT_SET(port, pin)          BIT_SET_MASK (port, 1 << (pin))
#define IS_BIT_SET(port, pin)       IS_BIT_SET_MASK (port, 1 << (pin))

#define MAKE_PIN_INPUT_PULLUP(ddrr, port, pin) \
    do {                                       \
        BIT_CLEAR (ddrr, pin);                 \
        BIT_SET (port, pin);                   \
    } while (0)
#define MAKE_PIN_INPUT_NO_PULLUP(ddrr, pin) BIT_CLEAR (ddrr, pin)
#define MAKE_PIN_OUTPUT(ddrr, pin)          BIT_SET (ddrr, pin)

void usart_off();
void usart_on();
void usart_send_char (char c);
void usart_send_string (const char* str);
