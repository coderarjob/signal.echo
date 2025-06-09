#include <main.h>
#include <stdbool.h>
#define YUKTI_TEST_IMPLEMENTATION
#include <yukti.h>
#include <mocks.h>
#include <assert.h>

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

    YT_MUST_CALL_IN_ORDER (usart_on);
    YT_MUST_CALL_IN_ORDER (loop_delay, YT_V (USART_TEST_DELAY_LOOP_COUNT));
    YT_MUST_CALL_IN_ORDER (usart_send_string, _);
    YT_MUST_CALL_IN_ORDER (usart_send_char, YT_V ('A'));
    YT_MUST_CALL_IN_ORDER (usart_send_char, YT_V ('B'));
    YT_MUST_CALL_IN_ORDER (usart_off);

    usart_test();

    YT_EQ_SCALAR (usart_send_string_fake.invokeCount, iter_num);

    YT_END();
}

YT_TEST (usart, usart_test_reset_after_char_overflow)
{
    unsigned int iter_num        = 'Z' - 'A' + 2;
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    YT_MUST_CALL_IN_ORDER (usart_send_char, YT_V ('Z'));
    YT_MUST_CALL_IN_ORDER (usart_send_char, YT_V ('A'));

    usart_test();

    YT_EQ_SCALAR (usart_send_string_fake.invokeCount, iter_num);

    YT_END();
}

YT_TEST (runt_pulse, runt_pulse_test_normal_pulses)
{
    unsigned int iter_num        = RUNT_PULSE_FREQ - 1;
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    YT_MUST_CALL_IN_ORDER (runt_pulse_init);
    YT_MUST_CALL_IN_ORDER (runt_pulse_body, YT_V (RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT),
                           YT_V (RUNT_TEST_NORMAL_HIGH_LEVEL), YT_V (RUNT_TEST_NORMAL_LOW_LEVEL));

    // Positive Runt pulse
    YT_MUST_NEVER_CALL (runt_pulse_body, _, YT_V (RUNT_TEST_RUNT_HIGH_LEVEL), _);

    // Negative Runt pulse
    YT_MUST_NEVER_CALL (runt_pulse_body, _, _, YT_V (RUNT_TEST_RUNT_LOW_LEVEL));

    YT_MUST_CALL_IN_ORDER (runt_pulse_exit);

    runt_pulse_test();

    YT_EQ_SCALAR (runt_pulse_body_fake.invokeCount, iter_num);

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

    YT_MUST_CALL_IN_ORDER (runt_pulse_init);

    // Normal pulse
    YT_MUST_CALL_IN_ORDER_ATLEAST_TIMES (iter_num - 4, runt_pulse_body,
                                         YT_V (RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT),
                                         YT_V (RUNT_TEST_NORMAL_HIGH_LEVEL),
                                         YT_V (RUNT_TEST_NORMAL_LOW_LEVEL));

    // Order of +ve or -ve runt pulse does not matter. We are verifying if both types of runt pulses
    // occur. We check twice to verify that internal states do flip after each runt pulse
    // generation.

    // Positive Runt pulse
    YT_MUST_CALL_ANY_ORDER_ATLEAST_TIMES (2, runt_pulse_body,
                                          YT_V (RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT),
                                          YT_V (RUNT_TEST_RUNT_HIGH_LEVEL),
                                          YT_V (RUNT_TEST_NORMAL_LOW_LEVEL));
    // Negative Runt pulse
    YT_MUST_CALL_ANY_ORDER_ATLEAST_TIMES (2, runt_pulse_body,
                                          YT_V (RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT),
                                          YT_V (RUNT_TEST_NORMAL_HIGH_LEVEL),
                                          YT_V (RUNT_TEST_RUNT_LOW_LEVEL));

    YT_MUST_CALL_IN_ORDER (runt_pulse_exit);

    runt_pulse_test();

    YT_EQ_SCALAR (runt_pulse_body_fake.invokeCount, iter_num);

    YT_END();
}

YT_TEST (two_pulses, two_pulse_test_normal)
{
    unsigned int iter_num        = 1;
    mode_is_dirty_fake.resources = &iter_num;
    mode_is_dirty_fake.handler   = mode_is_dirty_after_some_iterations_handler;

    YT_MUST_CALL_IN_ORDER (two_pulses_test_init);

    YT_MUST_CALL_IN_ORDER (two_pulses_test_body, YT_V (false),
                           YT_V (TWO_PULSES_TEST_NUMBER_OF_PULSES),
                           YT_V (TWO_PULSES_TEST_PULSE_WIDTH));

    YT_MUST_CALL_IN_ORDER (loop_delay, YT_V (TWO_PULSES_TEST_DELAY_LOOP_COUNT));

    YT_MUST_CALL_IN_ORDER (two_pulses_test_body, YT_V (true),
                           YT_V (TWO_PULSES_TEST_NUMBER_OF_PULSES),
                           YT_V (TWO_PULSES_TEST_PULSE_WIDTH));

    YT_MUST_CALL_IN_ORDER (loop_delay, YT_V (TWO_PULSES_TEST_DELAY_LOOP_COUNT));

    YT_MUST_CALL_IN_ORDER (two_pulses_test_exit);

    two_pulses_test();

    YT_EQ_SCALAR (two_pulses_test_body_fake.invokeCount, 2 * iter_num);

    YT_END();
}

void reset()
{
    reset_all_mocks();
}

int main (void)
{
    usart_test_normal();
    usart_test_reset_after_char_overflow();
    runt_pulse_test_normal_pulses();
    runt_pulse_test_runt_pulses();
    two_pulse_test_normal();
    return 0;
}
