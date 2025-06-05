#include <main.h>
#include <stdbool.h>
#define YUKTI_TEST_IMPLEMENTATION
#include <yukti.h>
#include <mocks.h>

bool mode_is_dirty_ofter_once_handler()
{
    return mode_is_dirty_fake.invokeCount > 1;
}

YT_TEST (test, usart_test_normal)
{
    mode_is_dirty_fake.handler = mode_is_dirty_ofter_once_handler;

    YT_MUST_CALL_IN_ORDER (usart_on);
    YT_MUST_CALL_IN_ORDER (loop_delay, YT_V (USART_TEST_DELAY_LOOP_COUNT));
    YT_MUST_CALL_IN_ORDER (usart_send_string, _);
    YT_MUST_CALL_IN_ORDER (usart_send_char, YT_V ('A'));
    YT_MUST_CALL_IN_ORDER (usart_off);

    usart_test();

    YT_EQ_SCALAR (true, true);

    YT_END();
}

YT_TEST (test, holdoff_test_normal)
{
    mode_is_dirty_fake.handler = mode_is_dirty_ofter_once_handler;

    YT_MUST_CALL_IN_ORDER (holdoff_test_init);
    YT_MUST_CALL_IN_ORDER (holdoff_test_body, YT_V (HOLDOFF_TEST_PULSE_WIDTH_LOOP_COUNT));
    YT_MUST_CALL_IN_ORDER (loop_delay, YT_V (HOLDOFF_TEST_GAP_DELAY_LOOP_COUNT));

    holdoff_test();

    YT_EQ_SCALAR (holdoff_test_body_fake.invokeCount, HOLDOFF_TEST_NUMBER_OF_PULSES);

    YT_END();
}

YT_TEST (test, runt_pulse_test_normal_pulses)
{
    mode_is_dirty_fake.handler = mode_is_dirty_ofter_once_handler;

    YT_MUST_CALL_IN_ORDER (runt_pulse_init);
    YT_MUST_CALL_IN_ORDER (runt_pulse_body, YT_V (RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT),
                           YT_V (RUNT_TEST_NORMAL_HIGH_LEVEL), YT_V (RUNT_TEST_NORMAL_LOW_LEVEL));

    YT_MUST_CALL_IN_ORDER (runt_pulse_exit);

    runt_pulse_test();

    YT_EQ_SCALAR (runt_pulse_body_fake.invokeCount, 1);

    YT_END();
}

bool mode_is_dirty_after_one_runt_pulse_handler()
{
    return mode_is_dirty_fake.invokeCount > RUNT_PULSE_FREQ;
}

YT_TEST (test, runt_pulse_test_runt_pulses)
{
    mode_is_dirty_fake.handler = mode_is_dirty_after_one_runt_pulse_handler;

    YT_MUST_CALL_IN_ORDER (runt_pulse_init);
    YT_MUST_CALL_IN_ORDER (runt_pulse_body, YT_V (RUNT_TEST_NORMAL_PULSE_WIDTH_LOOP_COUNT),
                           YT_V (RUNT_TEST_NORMAL_HIGH_LEVEL), YT_V (RUNT_TEST_NORMAL_LOW_LEVEL));
    YT_MUST_CALL_IN_ORDER (runt_pulse_body, YT_V (RUNT_TEST_RUNT_PULSE_WIDTH_LOOP_COUNT),
                           YT_V (RUNT_TEST_RUNT_HIGH_LEVEL), YT_V (RUNT_TEST_NORMAL_LOW_LEVEL));
    YT_MUST_CALL_IN_ORDER (runt_pulse_exit);

    runt_pulse_test();

    YT_EQ_SCALAR (runt_pulse_body_fake.invokeCount, RUNT_PULSE_FREQ + 1);

    YT_END();
}

void reset()
{
    YT_RESET_MOCK (mode_is_dirty);
}

int main (void)
{
    usart_test_normal();
    holdoff_test_normal();
    runt_pulse_test_normal_pulses();
    runt_pulse_test_runt_pulses();
    return 0;
}
