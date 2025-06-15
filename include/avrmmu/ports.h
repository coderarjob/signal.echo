#pragma once

#include <avr/io.h>
#include <utils.h>

#define DIGITAL_OUTPUT_PORT            PORTD
#define DIGITAL_OUTPUT_DDR             DDRD
#define DIGITAL_OUTPUT_PIN_NO0         PD0
#define DIGITAL_OUTPUT_PIN_NO1         PD1

#define ANALOG_OUTPUT_PORT             PORTC
#define ANALOG_OUTPUT_DDR              DDRC
#define ANALOG_OUTPUT_PIN_SHIFT        0
#define ANALOG_OUTPUT_PIN_COUNT        6
#define ANALOG_OUTPUT_PIN_MASK         BIT_MASK (ANALOG_OUTPUT_PIN_SHIFT, ANALOG_OUTPUT_PIN_COUNT)

#define SWITCH_PIN_NO                  PD2
#define SWITCH_PORT                    PORTD
#define SWITCH_PIN                     PIND
#define SWITCH_DDR                     DDRD

#define STATUS_PIN_NO                  PB1
#define STATUS_PORT                    PORTB
#define STATUS_PIN                     PINB
#define STATUS_DDR                     DDRB

#define RUNT_OUTPUT_PORT               ANALOG_OUTPUT_PORT
#define RUNT_OUTPUT_DDR                ANALOG_OUTPUT_DDR

#define HOLDOFF_OUTPUT_PIN_NO          DIGITAL_OUTPUT_PIN_NO0
#define HOLDOFF_OUTPUT_PORT            DIGITAL_OUTPUT_PORT
#define HOLDOFF_OUTPUT_DDR             DIGITAL_OUTPUT_DDR

#define TWO_PULSES_TEST_OUTPUT_PIN_NO0 DIGITAL_OUTPUT_PIN_NO0
#define TWO_PULSES_TEST_OUTPUT_PIN_NO1 DIGITAL_OUTPUT_PIN_NO1
#define TWO_PULSES_TEST_OUTPUT_PORT    DIGITAL_OUTPUT_PORT
#define TWO_PULSES_TEST_OUTPUT_DDR     DIGITAL_OUTPUT_DDR

#define BAUD                           10000
#define BAUD_COUNTER                   (((unsigned int)F_CPU / (16 * BAUD)) - 1)

#define MAKE_PIN_INPUT_PULLUP(ddrr, port, pin) \
    do {                                       \
        BIT_CLEAR (ddrr, pin);                 \
        BIT_SET (port, pin);                   \
    } while (0)
#define MAKE_PIN_INPUT_NO_PULLUP(ddrr, pin) BIT_CLEAR (ddrr, pin)
#define MAKE_PIN_OUTPUT(ddrr, pin)          BIT_SET (ddrr, pin)
