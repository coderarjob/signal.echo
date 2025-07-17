#include <main.h>
#include <hal.h>
#if HW_VER == 1
    #include <hw/v1/hwspec.h>
#endif
#include <hw/hwdetect.h>

void irq_switch_pressed()
{
    mode_advance();
    HAL_LOOP_DELAY (65535);
    while (!IS_BIT_SET (HAL_IO_IN_READ (SWITCH_INPUT_GPIO), SWITCH_INPUT_GPIO_PIN))
        ;
}

#if MPU_ARCH == AVR
    #include <avr/interrupt.h>
ISR (INT0_vect)
{
    irq_switch_pressed();
}
#endif // MPU_ARCH == AVR
