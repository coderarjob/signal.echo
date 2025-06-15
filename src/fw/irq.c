#include <main.h>
#if MPU_ARCH == AVR
    #include <avrmmu/hwmain.h>
#endif

void irq_switch_pressed()
{
    mode_advance();
    loop_delay(65535);
    while(is_switch_pressed());
}
