#include <arch/avr/hal.h>
#include <stdint.h>
#include <utils.h>

#define UNREACHABLE() hal_impl_panic()

void hal_usart_wait_transmit_complete()
{
    while ((UCSRA & (1 << UDRE)) == 0)
        ;
}

void hal_usart_on (uint32_t baud)
{
    UBRRH = HIGH8_16BITS (HAL_BAUD_COUNTER (baud, F_CPU));
    UBRRL = LOW8 (HAL_BAUD_COUNTER (baud, F_CPU));

    BIT_SET_MASK (UCSRC, (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0) | (1 << USBS));
    BIT_SET_MASK (UCSRB, (1 << TXEN));
}

void hal_usart_off()
{
    hal_usart_wait_transmit_complete();
    BIT_CLEAR_MASK (UCSRB, (1 << TXEN));
}

void hal_usart_send_string (const char* str)
{
    char c;
    while ((c = *str++)) {
        hal_usart_send_char (c);
    }
}

void hal_usart_send_char (char c)
{
    hal_usart_wait_transmit_complete();
    UDR = c;
}

void hal_interrupt_enable (HAL_Interrupts interrupt)
{
    if ((AVR_HAL_Interrupts)interrupt == AVR_HAL_INTERRUPTS_EXT_INTERRUPT0) {
        BIT_CLEAR_MASK (MCUCR, (1 << ISC01 | 1 << ISC00)); // Trigger at Low level
        BIT_SET_MASK (GICR, (1 << INT0));                  // Enable the interrupt
    } else if ((AVR_HAL_Interrupts)interrupt == AVR_HAL_INTERRUPTS_TIM0_OVF_INTERRUPT) {
        BIT_SET_MASK (TIMSK, (1 << TOIE0)); // Enable Timer 0 overflow interrupt
    } else {
        UNREACHABLE();
    }
}
