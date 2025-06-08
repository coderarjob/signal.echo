#pragma once

#include <stdbool.h>
#include <stdint.h>

#define USART_TEST_DELAY_LOOP_COUNT             65535U
#define USART_TEST_STRING                       "Hello"

#define HOLDOFF_TEST_NUMBER_OF_PULSES           20U
#define HOLDOFF_TEST_PULSE_WIDTH_LOOP_COUNT     255U
#define HOLDOFF_TEST_GAP_DELAY_LOOP_COUNT       65535U

#define RUNT_PULSE_FREQ                         1000 // 1 runt pulse after this many pulses
#define RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT   255U
#define RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT 512U

#define RUNT_TEST_RUNT_HIGH_LEVEL               0x7U
#define RUNT_TEST_RUNT_LOW_LEVEL                0x7U
#define RUNT_TEST_NORMAL_HIGH_LEVEL             0xFU // 0xF is full rail high
#define RUNT_TEST_NORMAL_LOW_LEVEL              0x0U // 0x0 is full rail low

#define TWO_PULSES_TEST_NUMBER_OF_PULSES        20U
#define TWO_PULSES_TEST_DELAY_LOOP_COUNT        65535U
#define TWO_PULSES_TEST_PULSE_WIDTH             255U

typedef enum TestModes {
    UNKNOWN_TEST,
    USART_TEST,
    HOLDOFF_TEST,
    RUNT_PULSE,
    TWO_PULSES_TEST,
    TEST_COUNT
} TestModes;

void mode_advance();
TestModes mode_get();
bool mode_is_dirty();

void hw_init();
void usart_off();
void usart_on();
void usart_send_char (char c);
void usart_send_string (const char* str);

void usart_test();

void holdoff_test();
void holdoff_test_body (uint16_t pulse_width);

void runt_pulse_test();
void runt_pulse_body (uint16_t pulse_width, uint8_t high_level, uint8_t low_level);

void two_pulses_test();
void two_pulses_test_body (bool isPrimaryPin, uint16_t num_pulses, uint16_t pulse_width);

void irq_switch_pressed();

