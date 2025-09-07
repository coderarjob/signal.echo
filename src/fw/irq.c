#include <main.h>
#include <hal.h>
#include <hw/hwspec.h>
#include <hw/hwdetect.h>

void irq_switch_pressed()
{
    mode_advance();
    HAL_LOOP_DELAY (65535);
    while (!IS_BIT_SET (HAL_IO_IN_READ (SWITCH_INPUT_GPIO), SWITCH_INPUT_GPIO_PIN))
        ;
}

#if ARCH == AVR
    #include <avr/interrupt.h>
ISR (INT0_vect)
{
    irq_switch_pressed();
}
#endif // ARCH == AVR
