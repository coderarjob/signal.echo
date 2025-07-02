#pragma once

#include <stdbool.h>
#include <stdint.h>
#if HW_VER == 1
    #include <hw/v1/hwspec.h>
#endif

#define USART_TEST_DELAY_LOOP_COUNT             65535U
#define USART_TEST_STRING                       "Hello"

#define RUNT_PULSE_FREQ                         1000 // 1 runt pulse after this many pulses
#define RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT   255U
#define RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT 512U

#define RUNT_TEST_RUNT_HIGH_LEVEL               ((DAC_WIDTH_MAX_VALUE / 2) - 1)
#define RUNT_TEST_RUNT_LOW_LEVEL                ((DAC_WIDTH_MAX_VALUE / 2) - 1)
#define RUNT_TEST_NORMAL_HIGH_LEVEL             (DAC_WIDTH_MAX_VALUE - 1)
#define RUNT_TEST_NORMAL_LOW_LEVEL              0x00U // 0x0 is full rail low

#define TWO_PULSES_TEST_NUMBER_OF_PULSES_PIN0   150U
#define TWO_PULSES_TEST_NUMBER_OF_PULSES_PIN1   300U
#define TWO_PULSES_TEST_DELAY_LOOP_COUNT        65535U
#define TWO_PULSES_TEST_PULSE_WIDTH             23U

#define SAWTOOTH_TEST_HIGH_LEVEL                (DAC_WIDTH_MAX_VALUE - 1)
#define SAWTOOTH_TEST_LOW_LEVEL                 0x00
#define SAWTOOTH_TEST_INCREMENT                 0x01

#define TRIANGLE_TEST_HIGH_LEVEL                (DAC_WIDTH_MAX_VALUE - 1)
#define TRIANGLE_TEST_LOW_LEVEL                 0x00
#define TRIANGLE_TEST_INCREMENT                 0x01

#define I2C_TEST_SCL_HOLD_DELAY                 10
#define I2C_TEST_STRING                         "Hello"

#define MODE_LED_VALUE_FROM_TESTMODE(state)     ((state) != TEST_MODE_ERROR ? (state) + 1 : (state))

typedef enum TestModes {
    TEST_MODE_USART_TEST      = 0,
    TEST_MODE_RUNT_PULSE_TEST = 1,
    TEST_MODE_TWO_PULSES_TEST = 2,
    TEST_MODE_SAWTOOTH_TEST   = 3,
    TEST_MODE_TRIANGLE_TEST   = 4,
    TEST_MODE_I2C_TEST        = 5,
    TEST_MODE_SINE_TEST       = 6,
    TEST_MODE_COUNT,
    TEST_MODE_ERROR = 7
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
void sine_test();
