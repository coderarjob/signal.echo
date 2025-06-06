#include <main.h>
#include <stdint.h>
#include <utils.h>
#include <avrmmu/ports.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay_basic.h>

ISR (INT0_vect)
{
    irq_switch_pressed();
}

void hw_init()
{
    // Make the Interrupt 0 pin as the input
    MAKE_PIN_INPUT_PULLUP (SWITCH_DDR, SWITCH_PORT, SWITCH_PIN_NO);

    // Enable interrupt
#if SWITCH_PIN_NO != PD2
    #error "Wrong switch pin set"
#endif

    BIT_CLEAR_MASK (MCUCR, (1 << ISC01 | 1 << ISC00)); // Trigger at Low level
    BIT_SET_MASK (GICR, (1 << INT0));                  // Enable the interrupt

    // Status port
    MAKE_PIN_OUTPUT (STATUS_DDR, STATUS_PIN_NO);
    BIT_CLEAR (STATUS_PORT, STATUS_PIN_NO);

    sei();
}

void holdoff_test_body (uint16_t pulse_width)
{
    BIT_SET (HOLDOFF_OUTPUT_PORT, HOLDOFF_OUTPUT_PIN_NO);
    _delay_loop_1 (pulse_width);
    BIT_CLEAR (HOLDOFF_OUTPUT_PORT, HOLDOFF_OUTPUT_PIN_NO);
    _delay_loop_1 (pulse_width);
}

void runt_pulse_body (uint16_t pulse_width, uint8_t high_level, uint8_t low_level)
{
    RUNT_OUTPUT_PORT = (high_level << 1); // Make PC1:PC4 as high
    _delay_loop_2 (pulse_width);
    RUNT_OUTPUT_PORT = (low_level << 1); // Make PC1:PC4 as high
    _delay_loop_2 (pulse_width);
}
