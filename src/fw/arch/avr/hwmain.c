#include <main.h>
#include <stdint.h>
#include <utils.h>
#include <avrmmu/ports.h>
#include <avr/interrupt.h>
#include <util/delay_basic.h>
#include <avrmmu/hwmain.h>

ISR (INT0_vect)
{
    irq_switch_pressed();
}

void hw_init()
{
    // ===========================================
    // Outputs
    // Make digital, analog and status led pins as output and clear them
    // ===========================================
    BIT_SET_MASK (DIGITAL_OUTPUT_DDR, DIGITAL_OUTPUT_MASK);
    BIT_CLEAR_MASK (DIGITAL_OUTPUT_PORT, DIGITAL_OUTPUT_MASK);

    BIT_SET_MASK (ANALOG_OUTPUT_DDR, ANALOG_OUTPUT_PIN_MASK);
    BIT_CLEAR_MASK (ANALOG_OUTPUT_PORT, ANALOG_OUTPUT_PIN_MASK);

    BIT_SET_MASK (STATUS_DDR, STATUS_OUT_REG_MASK);
    BIT_CLEAR_MASK (STATUS_PORT, STATUS_OUT_REG_MASK);

    // ===========================================
    // Inputs
    // Make switch pin as input and enable pullup
    // ===========================================
    // Make the Interrupt 0 pin as the input

#if SWITCH_PIN_NO != PD2
    #error "Wrong switch pin set"
#endif

    MAKE_PIN_INPUT_PULLUP (SWITCH_DDR, SWITCH_PORT, SWITCH_PIN_NO);

    // Enable interrupt
    BIT_CLEAR_MASK (MCUCR, (1 << ISC01 | 1 << ISC00)); // Trigger at Low level
    BIT_SET_MASK (GICR, (1 << INT0));                  // Enable the interrupt

    sei();
}

void runt_pulse_body (uint16_t pulse_width, uint8_t high_level, uint8_t low_level)
{
    RUNT_OUTPUT_PORT = high_level & ANALOG_OUTPUT_PIN_MASK;
    _delay_loop_2 (pulse_width);
    RUNT_OUTPUT_PORT = low_level & ANALOG_OUTPUT_PIN_MASK;
    _delay_loop_2 (pulse_width);
}

void two_pulses_test_body (bool isPrimaryPin, uint16_t num_pulses, uint16_t pulse_width)
{
    uint8_t pin = (isPrimaryPin) ? TWO_PULSES_TEST_OUTPUT_PIN_NO0 : TWO_PULSES_TEST_OUTPUT_PIN_NO1;

    while (num_pulses--) {
        BIT_SET (TWO_PULSES_TEST_OUTPUT_PORT, pin);
        _delay_loop_2 (pulse_width);
        BIT_CLEAR (TWO_PULSES_TEST_OUTPUT_PORT, pin);
        _delay_loop_2 (pulse_width);
    }
}
