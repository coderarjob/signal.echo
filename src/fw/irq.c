#include <main.h>
#if MPU_ARCH == AVR
    #include <avrmmu/hwmain.h>
#endif

void irq_switch_pressed()
{
    mode_advance();
    status_led_on();

    while(is_switch_pressed());

    status_led_off();
}
