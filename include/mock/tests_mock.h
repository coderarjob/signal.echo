#pragma once

#include <main.h>
#include <yukti.h>

YT_DECLARE_FUNC_VOID (usart_test);
YT_DECLARE_FUNC_VOID (runt_pulse_test);
YT_DECLARE_FUNC_VOID (two_pulses_test);
YT_DECLARE_FUNC_VOID (sawtooth_test);
YT_DECLARE_FUNC_VOID (triangle_test);
YT_DECLARE_FUNC_VOID (i2c_test);
YT_DECLARE_FUNC_VOID (sine_test);
YT_DECLARE_FUNC_VOID (sine_x_on_x_test);
YT_DECLARE_FUNC_VOID (am_test);

YT_DEFINE_FUNC_VOID (usart_test);
YT_DEFINE_FUNC_VOID (runt_pulse_test);
YT_DEFINE_FUNC_VOID (two_pulses_test);
YT_DEFINE_FUNC_VOID (sawtooth_test);
YT_DEFINE_FUNC_VOID (triangle_test);
YT_DEFINE_FUNC_VOID (i2c_test);
YT_DEFINE_FUNC_VOID (sine_test);
YT_DEFINE_FUNC_VOID (sine_x_on_x_test);
YT_DEFINE_FUNC_VOID (am_test);

void rest_test_mocks()
{
    YT_RESET_MOCK (usart_test);
    YT_RESET_MOCK (runt_pulse_test);
    YT_RESET_MOCK (two_pulses_test);
    YT_RESET_MOCK (sawtooth_test);
    YT_RESET_MOCK (triangle_test);
    YT_RESET_MOCK (i2c_test);
    YT_RESET_MOCK (sine_test);
    YT_RESET_MOCK (sine_x_on_x_test);
    YT_RESET_MOCK (am_test);
}
