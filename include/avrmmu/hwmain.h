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

static inline void set_status_led (uint8_t state)
{
    BIT_CLEAR_MASK(STATUS_PORT, STATUS_OUT_REG_MASK);
    STATUS_PORT |= (state << STATUS_OUT_REG_SHIFT) & STATUS_OUT_REG_MASK;
}

static inline void status_led_off()
{
    set_status_led (0);
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
void set_status_led (uint8_t state);
bool is_switch_pressed();
void loop_delay (uint16_t count);
void runt_pulse_init();
void runt_pulse_exit();
void two_pulses_test_exit();
void two_pulses_test_init();
#endif
