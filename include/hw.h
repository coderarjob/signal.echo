#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <avrmmu/hwmain.h>

void hw_init();
void usart_off();
void usart_on();
void usart_send_char (char c);
void usart_send_string (const char* str);
void holdoff_test_body (uint16_t pulse_width);
void runt_pulse_body (uint16_t pulse_width, uint8_t high_level, uint8_t low_level);
