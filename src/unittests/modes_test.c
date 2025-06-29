#include <main.h>
#include <stdio.h>
#define YUKTI_TEST_IMPLEMENTATION
#include <yukti.h>

YT_TEST (mode, default_mode_after_reset)
{
    mode_reset();
    YT_EQ_SCALAR ((int)mode_get(), USART_TEST);

    YT_END();
}

YT_TEST (mode, modes_advance_test)
{
    TestModes modes_exp[]        = { USART_TEST,    RUNT_PULSE,    TWO_PULSES_TEST,
                                     SAWTOOTH_TEST, TRIANGLE_TEST, I2C_TEST };
    const size_t modes_exp_count = sizeof (modes_exp) / sizeof (USART_TEST);

    // We should be checking every test, so modes_exp must have TEST_COUNT number of items
    YT_EQ_SCALAR ((int)modes_exp_count, TEST_COUNT);

    for (size_t i = 0; i < modes_exp_count; i++) {
        YT_EQ_SCALAR (mode_get(), modes_exp[i]);
        mode_advance();
    }

    YT_END();
}

YT_TEST (mode, modes_reset_after_full_cycle)
{
    // Must start with the default mode
    YT_EQ_SCALAR ((int)mode_get(), USART_TEST);

    // Advancing TEST_COUNT number of times should reset the mode to its start
    for (size_t i = 0; i < TEST_COUNT; i++) {
        mode_advance();
    }

    // Must be back to the default mode
    YT_EQ_SCALAR ((int)mode_get(), USART_TEST);

    YT_END();
}

void reset()
{
    mode_reset();
}

int main()
{
    YT_INIT();
    default_mode_after_reset();
    modes_advance_test();
    modes_reset_after_full_cycle();
    YT_RETURN_WITH_REPORT();
}
