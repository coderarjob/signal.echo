#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifndef UNITTESTS
#include <util/delay_basic.h>
#include <avrmmu/ports.h>
#include <utils.h>

static inline void two_pulses_test_init()
{
    BIT_SET_MASK (TWO_PULSES_TEST_OUTPUT_DDR,
                  (1 << TWO_PULSES_TEST_OUTPUT_PIN_NO0) | (1 << TWO_PULSES_TEST_OUTPUT_PIN_NO1));
    BIT_CLEAR_MASK (TWO_PULSES_TEST_OUTPUT_PORT,
                    (1 << TWO_PULSES_TEST_OUTPUT_PIN_NO0) | (1 << TWO_PULSES_TEST_OUTPUT_PIN_NO1));
}

static inline void two_pulses_test_exit()
{
    BIT_CLEAR_MASK (TWO_PULSES_TEST_OUTPUT_PORT,
                    (1 << TWO_PULSES_TEST_OUTPUT_PIN_NO0) | (1 << TWO_PULSES_TEST_OUTPUT_PIN_NO1));
}

static inline void runt_pulse_exit()
{
    RUNT_OUTPUT_PORT = 0x0; // Make all pins low
}

static inline void runt_pulse_init()
{
    RUNT_OUTPUT_DDR = 0xFF; // Make every pin as output
}

static inline void status_led_off()
{
    BIT_CLEAR (STATUS_PORT, STATUS_PIN_NO);
}

static inline void status_led_on()
{
    BIT_SET (STATUS_PORT, STATUS_PIN_NO);
}

static inline bool is_switch_pressed()
{
    // Set = Unpressed, Clear = Pressed
    return !IS_BIT_SET (SWITCH_PIN, SWITCH_PIN_NO);
}

static inline void loop_delay (uint16_t count)
{
    _delay_loop_2 (count);
}
#else
void status_led_off();
void status_led_on();
bool is_switch_pressed();
void loop_delay (uint16_t count);
void runt_pulse_init();
void runt_pulse_exit();
void two_pulses_test_exit();
void two_pulses_test_init();
#endif
