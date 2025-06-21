#pragma once

#include <stdint.h>
#include <yukti.h>

#define HAL_GPIO_A      0
#define HAL_GPIO_A_PIN0 0
#define HAL_GPIO_A_PIN1 1
#define HAL_GPIO_A_PIN2 2
#define HAL_GPIO_A_PIN3 3
#define HAL_GPIO_A_PIN4 4
#define HAL_GPIO_A_PIN5 5
#define HAL_GPIO_A_PIN6 6
#define HAL_GPIO_A_PIN7 7

#define HAL_GPIO_B      1
#define HAL_GPIO_B_PIN0 0
#define HAL_GPIO_B_PIN1 1
#define HAL_GPIO_B_PIN2 2
#define HAL_GPIO_B_PIN3 3
#define HAL_GPIO_B_PIN4 4
#define HAL_GPIO_B_PIN5 5
#define HAL_GPIO_B_PIN6 6
#define HAL_GPIO_B_PIN7 7

#define HAL_GPIO_C      2
#define HAL_GPIO_C_PIN0 0
#define HAL_GPIO_C_PIN1 1
#define HAL_GPIO_C_PIN2 2
#define HAL_GPIO_C_PIN3 3
#define HAL_GPIO_C_PIN4 4
#define HAL_GPIO_C_PIN5 5
#define HAL_GPIO_C_PIN6 6
#define HAL_GPIO_C_PIN7 7

#define HAL_GPIO_D      3
#define HAL_GPIO_D_PIN0 0
#define HAL_GPIO_D_PIN1 1
#define HAL_GPIO_D_PIN2 2
#define HAL_GPIO_D_PIN3 3
#define HAL_GPIO_D_PIN4 4
#define HAL_GPIO_D_PIN5 5
#define HAL_GPIO_D_PIN6 6
#define HAL_GPIO_D_PIN7 7

#define HAL_GPIO_MAX    HAL_GPIO_D
#define HAL_GPIO_MIN    HAL_GPIO_A

YT_DECLARE_FUNC_VOID (HAL_IO_OUT_WRITE_BITS, uint8_t, uint8_t, uint8_t, uint8_t);
YT_DECLARE_FUNC_VOID (HAL_IO_OUT_WRITE, uint8_t, uint8_t);
YT_DECLARE_FUNC (uint8_t, HAL_IO_IN_READ, uint8_t);

YT_DECLARE_FUNC_VOID (HAL_IO_OUT_LOW, uint8_t, uint8_t);
YT_DECLARE_FUNC_VOID (HAL_IO_OUT_HIGH, uint8_t, uint8_t);

YT_DECLARE_FUNC_VOID (HAL_IO_MAKE_INPUT_NO_PULLUP, uint8_t, uint8_t);
YT_DECLARE_FUNC_VOID (HAL_IO_MAKE_INPUT_WITH_PULLUP, uint8_t, uint8_t);
YT_DECLARE_FUNC_VOID (HAL_IO_MAKE_OUTPUT, uint8_t, uint8_t);

YT_DECLARE_FUNC_VOID (HAL_LOOP_DELAY, uint16_t);

typedef enum HAL_Interrupts {
    HAL_Interrupt_External0
} HAL_Interrupts;

YT_DECLARE_FUNC_VOID (HAL_INTERRUPT_SET);
YT_DECLARE_FUNC_VOID (HAL_INTERRUPT_CLEAR);
YT_DECLARE_FUNC_VOID (hal_interrupt_enable, HAL_Interrupts);

YT_DECLARE_FUNC_VOID (hal_usart_on, uint32_t);
YT_DECLARE_FUNC_VOID (hal_usart_off);
YT_DECLARE_FUNC_VOID (hal_usart_send_string, const char*);
YT_DECLARE_FUNC_VOID (hal_usart_send_char, char);
YT_DECLARE_FUNC_VOID (hal_usart_wait_transmit_complete);

/************************************************************************/

void HAL_IO_OUT_WRITE_BITS (uint8_t, uint8_t, uint8_t, uint8_t);
void HAL_IO_OUT_WRITE (uint8_t, uint8_t);
uint8_t HAL_IO_IN_READ (uint8_t);
void HAL_IO_OUT_LOW (uint8_t, uint8_t);
void HAL_IO_OUT_HIGH (uint8_t, uint8_t);
void HAL_IO_MAKE_INPUT_NO_PULLUP (uint8_t, uint8_t);
void HAL_IO_MAKE_INPUT_WITH_PULLUP (uint8_t, uint8_t);
void HAL_IO_MAKE_OUTPUT (uint8_t, uint8_t);
void HAL_LOOP_DELAY (uint16_t);
void HAL_INTERRUPT_SET();
void HAL_INTERRUPT_CLEAR();
void hal_interrupt_enable (HAL_Interrupts);
void hal_usart_on (uint32_t);
void hal_usart_off();
void hal_usart_send_string (const char*);
void hal_usart_send_char (char);
void hal_usart_wait_transmit_complete();

/************************************************************************/
