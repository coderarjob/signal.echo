#define YUKTI_TEST_IMPLEMENTATION
#include <yukti.h>
#include <main.h>
#include <hal.h>
#include <tests_mock.h>
#include <hal_mock.h>
#include <mode_mock.h>
#if HW_VER == 1
    #include <hw/v1/hwspec.h>
#endif

void fw_main (void);

YT_TEST (fwmain, hw_init_test)
{
    // Output GPIOs
    YT_MUST_CALL_ANY_ORDER (HAL_IO_MAKE_OUTPUT, YT_V (DIGITAL_OUTPUT_GPIO),
                            YT_V (DIGITAL_OUTPUT_PIN_MASK));
    YT_MUST_CALL_ANY_ORDER (HAL_IO_MAKE_OUTPUT, YT_V (ANALOG_OUTPUT_GPIO),
                            YT_V (ANALOG_OUTPUT_PIN_MASK));
    YT_MUST_CALL_ANY_ORDER (HAL_IO_MAKE_OUTPUT, YT_V (STATUS_OUTPUT_GPIO),
                            YT_V (STATUS_OUTPUT_PIN_MASK));

    // Input GPIOs
    YT_MUST_CALL_ANY_ORDER (HAL_IO_MAKE_INPUT_WITH_PULLUP, YT_V (SWITCH_INPUT_GPIO),
                            YT_V (SWITCH_INPUT_PIN_MASK));
    YT_MUST_CALL_ANY_ORDER (hal_interrupt_enable, YT_V (SWITCH_INPUT_INTERRUPT));

    // Enable interrupts
    YT_MUST_CALL_ANY_ORDER (HAL_INTERRUPT_SET);

    /* DUT function call */
    fw_main();

    YT_END();
}

YT_TESTP (fwmain, valid_mode_switch, TestModes)
{
    TestModes mode = YT_ARG_0();

    /* Setup */
    mode_get_fake.ret = mode;

    /* Expectations */
    YT_MUST_NEVER_CALL (hal_impl_panic);

    // mode_reset was called
    YT_MUST_CALL_IN_ORDER (mode_reset);

    // set_status_led function
    YT_MUST_CALL_IN_ORDER (HAL_IO_OUT_WRITE_BITS, YT_V (STATUS_OUTPUT_GPIO),
                           YT_V (MODE_LED_VALUE_FROM_TESTMODE (mode)),
                           YT_V (STATUS_OUTPUT_PIN_SHIFT), YT_V (STATUS_OUTPUT_PIN_MASK));

    // feature function called based on mode
    switch (mode_get()) {
    case TEST_MODE_USART_TEST:
        YT_MUST_CALL_IN_ORDER (usart_test);
        break;
    case TEST_MODE_RUNT_PULSE_TEST:
        YT_MUST_CALL_IN_ORDER (runt_pulse_test);
        break;
    case TEST_MODE_TWO_PULSES_TEST:
        YT_MUST_CALL_IN_ORDER (two_pulses_test);
        break;
    case TEST_MODE_SAWTOOTH_TEST:
        YT_MUST_CALL_IN_ORDER (sawtooth_test);
        break;
    case TEST_MODE_TRIANGLE_TEST:
        YT_MUST_CALL_IN_ORDER (triangle_test);
        break;
    case TEST_MODE_I2C_TEST:
        YT_MUST_CALL_IN_ORDER (i2c_test);
        break;
    case TEST_MODE_SINE_TEST:
        YT_MUST_CALL_IN_ORDER (sine_test);
        break;
    case TEST_MODE_SINE_X_ON_X_TEST:
        YT_MUST_CALL_IN_ORDER (sine_x_on_x_test);
        break;
    case TEST_MODE_AMP_MOD_TEST:
        YT_MUST_CALL_IN_ORDER (am_test);
        break;
    default:
        YT_EQ_SCALAR (false, true);
        break;
    }

    /* DUT function call */
    fw_main();

    YT_END();
}

YT_TEST (fwmain, invalid_mode_switch)
{
    TestModes mode = TEST_MODE_COUNT;

    /* Setup */
    mode_get_fake.ret = mode;

    /* Expectations */
    YT_MUST_CALL_ANY_ORDER(hal_impl_panic);

    /* DUT function call */
    fw_main();

    YT_END();
}

void yt_reset()
{
    reset_hal_mocks();
    reset_mode_mocks();
    rest_test_mocks();
}

int main()
{
    YT_INIT();
    hw_init_test();
    valid_mode_switch (TEST_MODE_COUNT,
                       YT_ARG (TestModes){ TEST_MODE_USART_TEST, TEST_MODE_RUNT_PULSE_TEST,
                                           TEST_MODE_TWO_PULSES_TEST, TEST_MODE_SAWTOOTH_TEST,
                                           TEST_MODE_TRIANGLE_TEST, TEST_MODE_I2C_TEST,
                                           TEST_MODE_SINE_TEST, TEST_MODE_SINE_X_ON_X_TEST,
                                           TEST_MODE_AMP_MOD_TEST });
    invalid_mode_switch();
    YT_RETURN_WITH_REPORT();
}
