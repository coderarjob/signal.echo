#pragma once

#include <main.h>
#include <stdint.h>
#include <yukti.h>
#include <stdbool.h>
#include <hal.h>

YT_DEFINE_FUNC_VOID (HAL_IO_OUT_WRITE_BITS, uint8_t, uint8_t, uint8_t, uint8_t);
YT_DEFINE_FUNC_VOID (HAL_IO_OUT_WRITE, uint8_t, uint8_t);
YT_DEFINE_FUNC(uint8_t, HAL_IO_IN_READ, uint8_t);

YT_DEFINE_FUNC_VOID (HAL_IO_OUT_LOW, uint8_t, uint8_t);
YT_DEFINE_FUNC_VOID (HAL_IO_OUT_HIGH, uint8_t, uint8_t);

YT_DEFINE_FUNC_VOID (HAL_IO_MAKE_INPUT_NO_PULLUP, uint8_t, uint8_t);
YT_DEFINE_FUNC_VOID (HAL_IO_MAKE_INPUT_WITH_PULLUP, uint8_t, uint8_t);
YT_DEFINE_FUNC_VOID (HAL_IO_MAKE_OUTPUT, uint8_t, uint8_t);

YT_DEFINE_FUNC_VOID (HAL_LOOP_DELAY, uint16_t);

YT_DEFINE_FUNC_VOID (HAL_INTERRUPT_SET);
YT_DEFINE_FUNC_VOID (HAL_INTERRUPT_CLEAR);
YT_DEFINE_FUNC_VOID (hal_interrupt_enable, HAL_Interrupts);

YT_DEFINE_FUNC_VOID (hal_usart_on, uint32_t);
YT_DEFINE_FUNC_VOID (hal_usart_off);
YT_DEFINE_FUNC_VOID (hal_usart_send_string, const char*);
YT_DEFINE_FUNC_VOID (hal_usart_send_char, char);
YT_DEFINE_FUNC_VOID (hal_usart_wait_transmit_complete);
// -----------------------------------------------------------------------------

void reset_hal_mocks()
{
    YT_RESET_MOCK (HAL_IO_OUT_WRITE_BITS);
    YT_RESET_MOCK (HAL_IO_OUT_WRITE);
    YT_RESET_MOCK (HAL_IO_IN_READ);
    YT_RESET_MOCK (HAL_IO_OUT_LOW);
    YT_RESET_MOCK (HAL_IO_OUT_HIGH);
    YT_RESET_MOCK (HAL_IO_MAKE_INPUT_NO_PULLUP);
    YT_RESET_MOCK (HAL_IO_MAKE_INPUT_WITH_PULLUP);
    YT_RESET_MOCK (HAL_IO_MAKE_OUTPUT);
    YT_RESET_MOCK (HAL_LOOP_DELAY);
    YT_RESET_MOCK (HAL_INTERRUPT_SET);
    YT_RESET_MOCK (HAL_INTERRUPT_CLEAR);
    YT_RESET_MOCK (hal_interrupt_enable);
    YT_RESET_MOCK (hal_usart_on);
    YT_RESET_MOCK (hal_usart_off);
    YT_RESET_MOCK (hal_usart_send_string);
    YT_RESET_MOCK (hal_usart_send_char);
    YT_RESET_MOCK (hal_usart_wait_transmit_complete);
}
