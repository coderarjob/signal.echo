#define YUKTI_TEST_IMPLEMENTATION
#include <yukti.h>
#include <main.h>
#include <stdbool.h>
#include <mode_mock.h>
#include <hal_mock.h>
#include <assert.h>
#if HW_VER == 1
    #include <hw/v1/hwspec.h>
#endif

bool mode_is_dirty_after_some_iterations_handler()
{
    assert (mode_is_dirty_fake.resources != NULL);
    return mode_is_dirty_fake.invokeCount > *((unsigned int*)mode_is_dirty_fake.resources);
}

YT_TEST (test, usart_test_normal)
{
    unsigned int iter_num        = 2;
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    YT_MUST_CALL_IN_ORDER (hal_usart_on, YT_V (HAL_IMPL_USART_BAUD));
    YT_MUST_CALL_IN_ORDER (HAL_LOOP_DELAY, YT_V (USART_TEST_DELAY_LOOP_COUNT));
    YT_MUST_CALL_IN_ORDER (hal_usart_send_string, _);
    YT_MUST_CALL_IN_ORDER (hal_usart_send_char, YT_V ('A'));
    YT_MUST_CALL_IN_ORDER (hal_usart_send_char, YT_V ('B'));
    YT_MUST_CALL_IN_ORDER (hal_usart_off);

    usart_test();

    YT_EQ_SCALAR (hal_usart_send_string_fake.invokeCount, iter_num);

    YT_END();
}

YT_TEST (usart, usart_test_reset_after_char_overflow)
{
    unsigned int iter_num        = 'Z' - 'A' + 2;
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    YT_MUST_CALL_IN_ORDER (hal_usart_send_char, YT_V ('Z'));
    YT_MUST_CALL_IN_ORDER (hal_usart_send_char, YT_V ('A'));

    usart_test();

    YT_EQ_SCALAR (hal_usart_send_string_fake.invokeCount, iter_num);

    YT_END();
}

YT_TEST (runt_pulse, runt_pulse_test_normal_pulses)
{
    unsigned int iter_num        = RUNT_PULSE_FREQ - 1;
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    // runt_pulse_test_init
    YT_MUST_CALL_IN_ORDER (HAL_IO_MAKE_OUTPUT, YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                           YT_V (RUNT_PULSE_TEST_OUTPUT_PIN_MASK));

    // runt_pulse_test_body - normal pulses
    YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_WRITE, YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                           YT_V (RUNT_TEST_NORMAL_HIGH_LEVEL));
    YT_MUST_CALL_IN_ORDER (HAL_LOOP_DELAY, YT_V (RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT));
    YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_WRITE, YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                           YT_V (RUNT_TEST_NORMAL_LOW_LEVEL));
    YT_MUST_CALL_IN_ORDER (HAL_LOOP_DELAY, YT_V (RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT));

    // runt_pulse_test_body - Positive Runt pulse (must never occur)
    YT_MUST_NEVER_CALL (HAL_IO_OUT_WRITE, _, YT_V (RUNT_TEST_RUNT_HIGH_LEVEL));

    // runt_pulse_test_body - Negative Runt pulse (must never occur)
    YT_MUST_NEVER_CALL (HAL_IO_OUT_WRITE, _, YT_V (RUNT_TEST_RUNT_LOW_LEVEL));

    // runt_pulse_test_exit
    YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_LOW, YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                           YT_V (RUNT_PULSE_TEST_OUTPUT_PIN_MASK));

    runt_pulse_test();

    YT_EQ_SCALAR (HAL_IO_OUT_WRITE_fake.invokeCount, iter_num * 2);

    YT_END();
}

YT_TEST (runt_pulse, runt_pulse_test_runt_pulses)
{
    unsigned int iter_num        = RUNT_PULSE_FREQ * 4; // We expect 4 runt pulses (2 +ve, 2 -ve)
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    // Total number of pulseses is iter_num (i.e RUNT_PULSE_FREQ * 4).
    // * 2 Positive Runt pulses
    // * 2 Negative Runt pulses
    // * iter_num - (2 + 2) Normal pulses

    // Notes: Given that the exact number of calls known, we should be using EXACT_TIMES macros
    // instead of ATLEAST onces, but the former does not exists yet!

    // runt_pulse_test_init
    YT_MUST_CALL_IN_ORDER (HAL_IO_MAKE_OUTPUT, YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                           YT_V (RUNT_PULSE_TEST_OUTPUT_PIN_MASK));

    // runt_pulse_test_body - Normal pulses
    // The order does not matter, we must have (iter_num - 2) normal +ve edges and the same number
    // of normal -ve edges.
    YT_MUST_CALL_ANY_ORDER_ATLEAST_TIMES (iter_num - 2, HAL_IO_OUT_WRITE,
                                          YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                                          YT_V (RUNT_TEST_NORMAL_HIGH_LEVEL));
    YT_MUST_CALL_ANY_ORDER_ATLEAST_TIMES (iter_num - 4, HAL_LOOP_DELAY,
                                          YT_V (RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT));
    YT_MUST_CALL_ANY_ORDER_ATLEAST_TIMES (iter_num - 2, HAL_IO_OUT_WRITE,
                                          YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                                          YT_V (RUNT_TEST_NORMAL_LOW_LEVEL));
    YT_MUST_CALL_ANY_ORDER_ATLEAST_TIMES (iter_num - 4, HAL_LOOP_DELAY,
                                          YT_V (RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT));

    // Order of +ve or -ve runt pulse does not matter. We are verifying if both types of runt pulses
    // occur. We check twice to verify that internal states do flip after each runt pulse
    // generation.

    // Positive Runt pulse
    YT_MUST_CALL_ANY_ORDER_ATLEAST_TIMES (2, HAL_IO_OUT_WRITE, YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                                          YT_V (RUNT_TEST_RUNT_HIGH_LEVEL));
    // Negative Runt pulse
    YT_MUST_CALL_ANY_ORDER_ATLEAST_TIMES (2, HAL_IO_OUT_WRITE, YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                                          YT_V (RUNT_TEST_RUNT_LOW_LEVEL));
    // Runt pulse width
    YT_MUST_CALL_ANY_ORDER_ATLEAST_TIMES (8, HAL_LOOP_DELAY,
                                          YT_V (RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT));

    // runt_pulse_test_exit
    YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_LOW, YT_V (RUNT_PULSE_TEST_OUTPUT_GPIO),
                           YT_V (RUNT_PULSE_TEST_OUTPUT_PIN_MASK));

    runt_pulse_test();

    YT_EQ_SCALAR (HAL_IO_OUT_WRITE_fake.invokeCount, iter_num * 2);

    YT_END();
}

YT_TEST (two_pulses, two_pulse_test_normal)
{
    unsigned int iter_num        = 1;
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    // two_pulses_test_init
    YT_MUST_CALL_IN_ORDER (HAL_IO_MAKE_OUTPUT, YT_V (TWO_PULSES_TEST_OUTPUT_GPIO),
                           YT_V (TWO_PULSES_TEST_OUTPUT_PIN_MASK));

    // two_pulses_test_body (gpio 0)
    for (unsigned int i = 0; i < TWO_PULSES_TEST_NUMBER_OF_PULSES_PIN0; i++) {
        YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_HIGH, YT_V (TWO_PULSES_TEST_OUTPUT_GPIO),
                               YT_V (TWO_PULSES_TEST_OUTPUT_PIN_NO0_MASK));
        YT_MUST_CALL_IN_ORDER (HAL_LOOP_DELAY, YT_V (TWO_PULSES_TEST_PULSE_WIDTH));
        YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_LOW, YT_V (TWO_PULSES_TEST_OUTPUT_GPIO),
                               YT_V (TWO_PULSES_TEST_OUTPUT_PIN_NO0_MASK));
        YT_MUST_CALL_IN_ORDER (HAL_LOOP_DELAY, YT_V (TWO_PULSES_TEST_PULSE_WIDTH));
    }

    // delay between two pulses (delay before gpio 1)
    YT_MUST_CALL_IN_ORDER (HAL_LOOP_DELAY, YT_V (TWO_PULSES_TEST_DELAY_LOOP_COUNT));

    // two_pulses_test_body (gpio 1)
    for (unsigned int i = 0; i < TWO_PULSES_TEST_NUMBER_OF_PULSES_PIN1; i++) {
        YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_HIGH, YT_V (TWO_PULSES_TEST_OUTPUT_GPIO),
                               YT_V (TWO_PULSES_TEST_OUTPUT_PIN_NO1_MASK));
        YT_MUST_CALL_IN_ORDER (HAL_LOOP_DELAY, YT_V (TWO_PULSES_TEST_PULSE_WIDTH));
        YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_LOW, YT_V (TWO_PULSES_TEST_OUTPUT_GPIO),
                               YT_V (TWO_PULSES_TEST_OUTPUT_PIN_NO1_MASK));
        YT_MUST_CALL_IN_ORDER (HAL_LOOP_DELAY, YT_V (TWO_PULSES_TEST_PULSE_WIDTH));
    }

    // delay between two pulses (delay before gpio 0)
    YT_MUST_CALL_IN_ORDER (HAL_LOOP_DELAY, YT_V (TWO_PULSES_TEST_DELAY_LOOP_COUNT));

    // runt_pulse_test_exit
    YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_LOW, YT_V (TWO_PULSES_TEST_OUTPUT_GPIO),
                           YT_V (TWO_PULSES_TEST_OUTPUT_PIN_MASK));

    two_pulses_test();

    YT_END();
}

YT_TEST (sawtooth, sawtooth_test_normal)
{
    unsigned int iter_num        = 2;
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    // sawtooth_test_init
    YT_MUST_CALL_IN_ORDER (HAL_IO_MAKE_OUTPUT, YT_V (SAWTOOTH_TEST_OUTPUT_GPIO),
                           YT_V (SAWTOOTH_TEST_OUTPUT_PIN_MASK));

    // sawtooth test body
    for (unsigned i = 0; i < iter_num; i++) {
        YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_WRITE, YT_V (SAWTOOTH_TEST_OUTPUT_GPIO),
                               YT_V (SAWTOOTH_TEST_LOW_LEVEL));

        YT_MUST_CALL_IN_ORDER_ATLEAST_TIMES (DAC_WIDTH_MAX_VALUE - 2, HAL_IO_OUT_WRITE,
                                             YT_V (SAWTOOTH_TEST_OUTPUT_GPIO), _);

        YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_WRITE, YT_V (SAWTOOTH_TEST_OUTPUT_GPIO),
                               YT_V (SAWTOOTH_TEST_HIGH_LEVEL));
    }

    // sawtooth_test_exit
    YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_LOW, YT_V (SAWTOOTH_TEST_OUTPUT_GPIO),
                           YT_V (SAWTOOTH_TEST_OUTPUT_PIN_MASK));
    sawtooth_test();
    YT_END();
}

YT_TEST (triangle, triangle_test_normal)
{
    unsigned int iter_num        = 2;
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    // triangle_test_init
    YT_MUST_CALL_IN_ORDER (HAL_IO_MAKE_OUTPUT, YT_V (TRIANGLE_TEST_OUTPUT_GPIO),
                           YT_V (TRIANGLE_TEST_OUTPUT_PIN_MASK));

    // triangle test body
    for (unsigned i = 0; i < iter_num; i++) {
        // triangle test body (rising edge)
        YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_WRITE, YT_V (TRIANGLE_TEST_OUTPUT_GPIO),
                               YT_V (TRIANGLE_TEST_LOW_LEVEL));

        YT_MUST_CALL_IN_ORDER_ATLEAST_TIMES (DAC_WIDTH_MAX_VALUE - 2, HAL_IO_OUT_WRITE,
                                             YT_V (TRIANGLE_TEST_OUTPUT_GPIO), _);

        // At the end of the rising edge we must have reached the HIGH level. Since that is also the
        // level at which the falling egde must start, we check this condition once.
        //
        // However depending on the implementation HAL_IO_OUT_WRITE (for the HIGH level) might get
        // called twice (once at the end of the rising ege and another immediately afterwards at the
        // start of the falling edge). Both these cases would be considered valid by this test.
        //
        // Similar thing happen at the transision fron falling to rising edge.

        // triangle test body (falling edge)
        YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_WRITE, YT_V (TRIANGLE_TEST_OUTPUT_GPIO),
                               YT_V (TRIANGLE_TEST_HIGH_LEVEL));

        YT_MUST_CALL_IN_ORDER_ATLEAST_TIMES (DAC_WIDTH_MAX_VALUE - 2, HAL_IO_OUT_WRITE,
                                             YT_V (TRIANGLE_TEST_OUTPUT_GPIO), _);
    }

    // triangle_test_exit
    YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_LOW, YT_V (TRIANGLE_TEST_OUTPUT_GPIO),
                           YT_V (TRIANGLE_TEST_OUTPUT_PIN_MASK));
    triangle_test();
    YT_END();
}

void yt_reset()
{
    reset_hal_mocks();
    reset_mode_mocks();
}

int main (void)
{
    YT_INIT();
    usart_test_normal();
    usart_test_reset_after_char_overflow();
    runt_pulse_test_normal_pulses();
    runt_pulse_test_runt_pulses();
    two_pulse_test_normal();
    sawtooth_test_normal();
    triangle_test_normal();
    YT_RETURN_WITH_REPORT();
}
