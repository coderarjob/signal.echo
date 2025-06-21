#include <hal.h>
#if HW_VER == 1
    #include <hw/v1/hwspec.h>
#endif
#include <stdint.h>
#include <main.h>

void usart_test()
{
    hal_usart_on (HAL_IMPL_USART_BAUD);
    char c = 'A';
    while (!mode_is_dirty()) {
        HAL_LOOP_DELAY (USART_TEST_DELAY_LOOP_COUNT);
        hal_usart_send_string (USART_TEST_STRING);
        hal_usart_send_char (c);

        if (++c > 'Z') {
            c = 'A';
        }
    }
    hal_usart_off();
}

static inline void runt_pulse_test_init()
{
    HAL_IO_MAKE_OUTPUT (RUNT_PULSE_TEST_OUTPUT_GPIO, RUNT_PULSE_TEST_OUTPUT_PIN_MASK);
}

static inline void runt_pulse_test_exit()
{
    HAL_IO_OUT_LOW (RUNT_PULSE_TEST_OUTPUT_GPIO, RUNT_PULSE_TEST_OUTPUT_PIN_MASK);
}

static void runt_pulse_test_body (uint8_t highLevel, uint8_t lowLevel, uint16_t pulseWidth)
{
    HAL_IO_OUT_WRITE (RUNT_PULSE_TEST_OUTPUT_GPIO, highLevel);
    HAL_LOOP_DELAY (pulseWidth);
    HAL_IO_OUT_WRITE (RUNT_PULSE_TEST_OUTPUT_GPIO, lowLevel);
    HAL_LOOP_DELAY (pulseWidth);
}

void runt_pulse_test()
{
    runt_pulse_test_init();

    // Number of runt pulses per 1000 normal pulses
    uint32_t runtFreq        = RUNT_PULSE_FREQ;
    bool isPositiveRuntPulse = true; // true: Runt when going high, false: Runt when going low.

    while (!mode_is_dirty()) {
        uint8_t lowLevel    = RUNT_TEST_NORMAL_LOW_LEVEL;
        uint8_t highLevel   = RUNT_TEST_NORMAL_HIGH_LEVEL;
        uint16_t pulseWidth = RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT;

        if (--runtFreq == 0) {
            runtFreq   = RUNT_PULSE_FREQ;
            pulseWidth = RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT;
            if (isPositiveRuntPulse) {
                highLevel = RUNT_TEST_RUNT_HIGH_LEVEL;
            } else {
                lowLevel = RUNT_TEST_RUNT_LOW_LEVEL;
            }
            isPositiveRuntPulse ^= 1;
        }

        runt_pulse_test_body (highLevel, lowLevel, pulseWidth);
    }

    runt_pulse_test_exit();
}

static inline void two_pulses_test_init()
{
    HAL_IO_MAKE_OUTPUT (TWO_PULSES_TEST_OUTPUT_GPIO, TWO_PULSES_TEST_OUTPUT_PIN_MASK);
}

static inline void two_pulses_test_exit()
{
    HAL_IO_OUT_LOW (TWO_PULSES_TEST_OUTPUT_GPIO, TWO_PULSES_TEST_OUTPUT_PIN_MASK);
}

static void two_pulses_test_body (bool isPrimaryPin, uint16_t num_pulses, uint16_t pulse_width)
{
    uint8_t mask = (isPrimaryPin) ? TWO_PULSES_TEST_OUTPUT_PIN_NO0_MASK
                                  : TWO_PULSES_TEST_OUTPUT_PIN_NO1_MASK;

    while (num_pulses--) {
        HAL_IO_OUT_HIGH (TWO_PULSES_TEST_OUTPUT_GPIO, mask);
        HAL_LOOP_DELAY (pulse_width);
        HAL_IO_OUT_LOW (TWO_PULSES_TEST_OUTPUT_GPIO, mask);
        HAL_LOOP_DELAY (pulse_width);
    }
}

void two_pulses_test()
{
    two_pulses_test_init();

    while (!mode_is_dirty()) {
        two_pulses_test_body (false, TWO_PULSES_TEST_NUMBER_OF_PULSES_PIN0,
                              TWO_PULSES_TEST_PULSE_WIDTH);
        HAL_LOOP_DELAY (TWO_PULSES_TEST_DELAY_LOOP_COUNT);
        two_pulses_test_body (true, TWO_PULSES_TEST_NUMBER_OF_PULSES_PIN1,
                              TWO_PULSES_TEST_PULSE_WIDTH);
        HAL_LOOP_DELAY (TWO_PULSES_TEST_DELAY_LOOP_COUNT);
    }

    two_pulses_test_exit();
}
