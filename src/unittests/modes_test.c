#define YUKTI_TEST_IMPLEMENTATION
#include <yukti.h>
#include <main.h>

YT_TEST (mode, default_mode_after_reset)
{
    mode_reset();
    YT_EQ_SCALAR ((int)mode_get(), TEST_MODE_USART_TEST);

    YT_END();
}

YT_TEST (mode, modes_advance_test)
{
    TestModes modes_exp[]        = { TEST_MODE_USART_TEST,      TEST_MODE_RUNT_PULSE_TEST,
                                     TEST_MODE_TWO_PULSES_TEST, TEST_MODE_SAWTOOTH_TEST,
                                     TEST_MODE_TRIANGLE_TEST,   TEST_MODE_I2C_TEST };
    const size_t modes_exp_count = sizeof (modes_exp) / sizeof (TEST_MODE_USART_TEST);

    // We should be checking every test, so modes_exp must have TEST_COUNT number of items
    YT_EQ_SCALAR ((int)modes_exp_count, TEST_MODE_COUNT);

    for (size_t i = 0; i < modes_exp_count; i++) {
        YT_EQ_SCALAR (mode_get(), modes_exp[i]);
        mode_advance();
    }

    YT_END();
}

YT_TEST (mode, modes_reset_after_full_cycle)
{
    // Must start with the default mode
    YT_EQ_SCALAR ((int)mode_get(), TEST_MODE_USART_TEST);

    // Advancing TEST_COUNT number of times should reset the mode to its start
    for (size_t i = 0; i < TEST_MODE_COUNT; i++) {
        mode_advance();
    }

    // Must be back to the default mode
    YT_EQ_SCALAR ((int)mode_get(), TEST_MODE_USART_TEST);

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
