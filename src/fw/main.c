#include <stdbool.h>
#include <stdint.h>
#include <main.h>
#include <hw.h>

__attribute__ ((noreturn)) int main (void)
{
    hw_init();
    while (1) {
        switch (mode_get()) {
        case USART_TEST:
            usart_test();
            break;
        case HOLDOFF_TEST:
            holdoff_test();
            break;
        case RUNT_PULSE:
            runt_pulse_test();
            break;
        default:
            status_led_on();
            break;
        }
    }
}

void usart_test()
{
    usart_on();
    char c = 'A';
    while (!mode_is_dirty()) {
        if (++c > 'Z') {
            c = 'A';
        }
        loop_delay (USART_TEST_DELAY_LOOP_COUNT);
        usart_send_string (USART_TEST_STRING);
        usart_send_char (c);
    }
    usart_off();
}

void holdoff_test()
{
    holdoff_test_init();

    while (!mode_is_dirty()) {
        for (int i = 0; i < HOLDOFF_TEST_NUMBER_OF_PULSES; i++) {
            holdoff_test_body (HOLDOFF_TEST_PULSE_WIDTH_LOOP_COUNT);
        }
        loop_delay (HOLDOFF_TEST_GAP_DELAY_LOOP_COUNT);
    }
}

void runt_pulse_test()
{
    runt_pulse_init();

    // Number of runt pulses per 1000 normal pulses
    uint32_t runtFreq = RUNT_PULSE_FREQ;

    while (!mode_is_dirty()) {
        if (--runtFreq) {
            runtFreq = RUNT_PULSE_FREQ;
            runt_pulse_body (RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT, RUNT_TEST_RUNT_HIGH_LEVEL,
                             RUNT_TEST_NORMAL_LOW_LEVEL);
        } else {
            runt_pulse_body (RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT, RUNT_TEST_NORMAL_HIGH_LEVEL,
                             RUNT_TEST_NORMAL_LOW_LEVEL);
        }
    }

    runt_pulse_exit();
}
