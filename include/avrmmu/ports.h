#pragma once

#include <avr/io.h>
#include <utils.h>

#define SWITCH_PIN_NO         PD2
#define SWITCH_PORT           PORTD
#define SWITCH_PIN            PIND
#define SWITCH_DDR            DDRD

#define STATUS_PIN_NO         PB1
#define STATUS_PORT           PORTB
#define STATUS_PIN            PINB
#define STATUS_DDR            DDRB

#define RUNT_OUTPUT_PORT      PORTC
#define RUNT_OUTPUT_DDR       DDRC

#define HOLDOFF_OUTPUT_PIN_NO PD1
#define HOLDOFF_OUTPUT_PORT   PORTD
#define HOLDOFF_OUTPUT_DDR    DDRD

#define BAUD                  10000
#define BAUD_COUNTER          (((unsigned int)F_CPU / (16 * BAUD)) - 1)

#define MAKE_PIN_INPUT_PULLUP(ddrr, port, pin) \
    do {                                       \
        BIT_CLEAR (ddrr, pin);                 \
        BIT_SET (port, pin);                   \
    } while (0)
#define MAKE_PIN_INPUT_NO_PULLUP(ddrr, pin) BIT_CLEAR (ddrr, pin)
#define MAKE_PIN_OUTPUT(ddrr, pin)          BIT_SET (ddrr, pin)
