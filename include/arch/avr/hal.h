#pragma once

#include <stdint.h>
#if !defined(UNITTESTS)
    #include <util/delay_basic.h>
    #include <avr/interrupt.h>
    #include <avr/io.h>
#endif // !defined (UNITTESTS)
#include <utils.h>
#include <stdbool.h>

/* ==============================================================================
 * AVR Specific items
 * ============================================================================== */
/* There are other interrupts, but for now it includes only those needed by this project */
typedef enum AVR_HAL_Interrupts {
    AVR_HAL_INTERRUPTS_EXT_INTERRUPT0,
} AVR_HAL_Interrupts;

#if !defined(UNITTESTS)
static inline bool hal_usart_is_transmit_complete()
{
    return (UCSRA & (1 << UDRE)) != 0;
}
#endif // !defined (UNITTESTS)

#define AVR_HAL_GPIO_A_PORT_REG PORTA
#define AVR_HAL_GPIO_A_PIN_REG  PINA
#define AVR_HAL_GPIO_A_DDR_REG  DDRA

#define AVR_HAL_GPIO_B_PORT_REG PORTB
#define AVR_HAL_GPIO_B_PIN_REG  PINB
#define AVR_HAL_GPIO_B_DDR_REG  DDRB

#define AVR_HAL_GPIO_C_PORT_REG PORTC
#define AVR_HAL_GPIO_C_PIN_REG  PINC
#define AVR_HAL_GPIO_C_DDR_REG  DDRC

#define AVR_HAL_GPIO_D_PORT_REG PORTD
#define AVR_HAL_GPIO_D_PIN_REG  PIND
#define AVR_HAL_GPIO_D_DDR_REG  DDRD

#define AVR_HAL_IO_OUT_WRITE_BITS(gpio, value, shift, mask) \
    do {                                                    \
        BIT_CLEAR_MASK (gpio##_PORT_REG, mask);             \
        gpio##_PORT_REG |= ((value << (shift)) & (mask));   \
    } while (0)

#define AVR_HAL_IO_OUT_WRITE(gpio, value)  (gpio##_PORT_REG = (value))
#define AVR_HAL_IO_IN_READ(gpio)           (gpio##_PIN_REG)

#define AVR_HAL_IO_OUT_LOW(gpio, mask)     BIT_CLEAR_MASK (gpio##_PORT_REG, mask)
#define AVR_HAL_IO_OUT_HIGH(gpio, mask)    BIT_SET_MASK (gpio##_PORT_REG, mask)

#define AVR_HAL_IO_MAKE_OUTPUT(gpio, mask) BIT_SET_MASK (gpio##_DDR_REG, mask)

#define AVR_HAL_IO_MAKE_INPUT_NO_PULLUP(gpio, mask) \
    do {                                            \
        BIT_CLEAR_MASK (gpio##_DDR_REG, mask);      \
        BIT_CLEAR_MASK (gpio##_PORT_REG, mask);     \
    } while (0)

#define AVR_HAL_IO_MAKE_INPUT_WITH_PULLUP(gpio, mask) \
    do {                                              \
        BIT_CLEAR_MASK (gpio##_DDR_REG, mask);        \
        BIT_SET_MASK (gpio##_PORT_REG, mask);         \
    } while (0)

/* ==============================================================================
 * Users of hal must provide these items
 * ============================================================================== */
// #define HAL_IMPL_USART_BAUD
__attribute__ ((noreturn)) void hal_impl_panic();

/* ==============================================================================
 * ARCH non-specific items
 * ============================================================================== */
#define HAL_GPIO_A      AVR_HAL_GPIO_A
#define HAL_GPIO_A_PIN0 PA0
#define HAL_GPIO_A_PIN1 PA1
#define HAL_GPIO_A_PIN2 PA2
#define HAL_GPIO_A_PIN3 PA3
#define HAL_GPIO_A_PIN4 PA4
#define HAL_GPIO_A_PIN5 PA5
#define HAL_GPIO_A_PIN6 PA6
#define HAL_GPIO_A_PIN7 PA7

#define HAL_GPIO_B      AVR_HAL_GPIO_B
#define HAL_GPIO_B_PIN0 PB0
#define HAL_GPIO_B_PIN1 PB1
#define HAL_GPIO_B_PIN2 PB2
#define HAL_GPIO_B_PIN3 PB3
#define HAL_GPIO_B_PIN4 PB4
#define HAL_GPIO_B_PIN5 PB5
#define HAL_GPIO_B_PIN6 PB6
#define HAL_GPIO_B_PIN7 PB7

#define HAL_GPIO_C      AVR_HAL_GPIO_C
#define HAL_GPIO_C_PIN0 PC0
#define HAL_GPIO_C_PIN1 PC1
#define HAL_GPIO_C_PIN2 PC2
#define HAL_GPIO_C_PIN3 PC3
#define HAL_GPIO_C_PIN4 PC4
#define HAL_GPIO_C_PIN5 PC5
#define HAL_GPIO_C_PIN6 PC6
#define HAL_GPIO_C_PIN7 PC7

#define HAL_GPIO_D      AVR_HAL_GPIO_D
#define HAL_GPIO_D_PIN0 PD0
#define HAL_GPIO_D_PIN1 PD1
#define HAL_GPIO_D_PIN2 PD2
#define HAL_GPIO_D_PIN3 PD3
#define HAL_GPIO_D_PIN4 PD4
#define HAL_GPIO_D_PIN5 PD5
#define HAL_GPIO_D_PIN6 PD6
#define HAL_GPIO_D_PIN7 PD7

#define HAL_GPIO_MAX    HAL_GPIO_D
#define HAL_GPIO_MIN    HAL_GPIO_A

#define HAL_IO_OUT_WRITE_BITS(gpio, value, shift, mask) \
    AVR_HAL_IO_OUT_WRITE_BITS (gpio, value, shift, mask);
#define HAL_IO_OUT_WRITE(gpio, value)             AVR_HAL_IO_OUT_WRITE (gpio, value)
#define HAL_IO_IN_READ(gpio)                      AVR_HAL_IO_IN_READ (gpio)

#define HAL_IO_OUT_LOW(gpio, mask)                AVR_HAL_IO_OUT_LOW (gpio, mask)
#define HAL_IO_OUT_HIGH(gpio, mask)               AVR_HAL_IO_OUT_HIGH (gpio, mask)

#define HAL_IO_MAKE_INPUT_NO_PULLUP(gpio, mask)   AVR_HAL_IO_MAKE_INPUT_NO_PULLUP (gpio, mask)
#define HAL_IO_MAKE_INPUT_WITH_PULLUP(gpio, mask) AVR_HAL_IO_MAKE_INPUT_WITH_PULLUP (gpio, mask)
#define HAL_IO_MAKE_OUTPUT(gpio, mask)            AVR_HAL_IO_MAKE_OUTPUT (gpio, mask)

#define HAL_LOOP_DELAY(count)                     _delay_loop_2 (count)

typedef enum HAL_Interrupts {
    HAL_Interrupt_External0 = AVR_HAL_INTERRUPTS_EXT_INTERRUPT0
} HAL_Interrupts;

#define HAL_INTERRUPT_SET()   sei()
#define HAL_INTERRUPT_CLEAR() cli()
void hal_interrupt_enable (HAL_Interrupts);

#define HAL_BAUD_COUNTER(baud) (((unsigned int)F_CPU / (16U * (baud))) - 1)
void hal_usart_on (uint32_t baud);
void hal_usart_off();
void hal_usart_send_string (const char* str);
void hal_usart_send_char (char c);
void hal_usart_wait_transmit_complete();
/* ============================================================================== */
