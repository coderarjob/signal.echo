#pragma once

#include <stdbool.h>
#include <stdint.h>

#define USART_TEST_DELAY_LOOP_COUNT             65535U
#define USART_TEST_STRING                       "Hello"

#define RUNT_PULSE_FREQ                         1000 // 1 runt pulse after this many pulses
#define RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT   255U
#define RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT 512U

#define RUNT_TEST_RUNT_HIGH_LEVEL               0x1FU
#define RUNT_TEST_RUNT_LOW_LEVEL                0x1FU
#define RUNT_TEST_NORMAL_HIGH_LEVEL             0x3FU // 0x3F is full rail high
#define RUNT_TEST_NORMAL_LOW_LEVEL              0x00U // 0x0 is full rail low

#define TWO_PULSES_TEST_NUMBER_OF_PULSES_PIN0   150U
#define TWO_PULSES_TEST_NUMBER_OF_PULSES_PIN1   300U
#define TWO_PULSES_TEST_DELAY_LOOP_COUNT        65535U
#define TWO_PULSES_TEST_PULSE_WIDTH             23U

#define DAC_WIDTH_BITS                          6U
#define DAC_WIDTH_MAX_VALUE                     64U

#define SAWTOOTH_TEST_HIGH_LEVEL                0x3F
#define SAWTOOTH_TEST_LOW_LEVEL                 0x00
#define SAWTOOTH_TEST_INCREMENT                 0x01

#define TRIANGLE_TEST_HIGH_LEVEL                0x3F
#define TRIANGLE_TEST_LOW_LEVEL                 0x00
#define TRIANGLE_TEST_INCREMENT                 0x01

#define I2C_TEST_SCL_HOLD_DELAY                 10
#define I2C_TEST_STRING                         "Hello"

typedef enum TestModes {
    UNKNOWN_TEST,
    USART_TEST,
    RUNT_PULSE,
    TWO_PULSES_TEST,
    SAWTOOTH_TEST,
    TRIANGLE_TEST,
    I2C_TEST,
    TEST_COUNT
} TestModes;

void mode_advance();
TestModes mode_get();
bool mode_is_dirty();
void mode_reset();

void usart_test();
void runt_pulse_test();
void two_pulses_test();
void sawtooth_test();
void triangle_test();
void i2c_test();
