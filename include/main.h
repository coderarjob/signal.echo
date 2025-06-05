#pragma once

#include <stdbool.h>

#define USART_TEST_DELAY_LOOP_COUNT             65535
#define USART_TEST_STRING                       "Hello"

#define HOLDOFF_TEST_NUMBER_OF_PULSES           20
#define HOLDOFF_TEST_PULSE_WIDTH_LOOP_COUNT     255
#define HOLDOFF_TEST_GAP_DELAY_LOOP_COUNT       65535

#define RUNT_PULSE_FREQ                         1000 // 1 runt pulse after this many pulses
#define RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT   255
#define RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT 512

#define RUNT_TEST_RUNT_HIGH_LEVEL               0x7
#define RUNT_TEST_RUNT_LOW_LEVEL                0x7
#define RUNT_TEST_NORMAL_HIGH_LEVEL             0xF // 0xF is full rail high
#define RUNT_TEST_NORMAL_LOW_LEVEL              0x0 // 0x0 is full rail low

typedef enum TestModes {
    UNKNOWN_TEST,
    USART_TEST,
    HOLDOFF_TEST,
    RUNT_PULSE,
    TEST_COUNT
} TestModes;

void mode_advance();
TestModes mode_get();
bool mode_is_dirty();

void usart_test();
void holdoff_test();
void runt_pulse_test();

void irq_switch_pressed();
