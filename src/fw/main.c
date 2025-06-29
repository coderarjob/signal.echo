#include <hal.h>
#if HW_VER == 1
    #include <hw/v1/hwspec.h>
#endif
#include <main.h>

#if defined(DEBUG)
void hwspec_sanity_check()
{
    #if MPU_ARCH == AVR && SWITCH_INPUT_GPIO_PIN != PD2
        #error "Wrong switch pin set"
    #endif

    #define CHECK_OVERLAP(comb, mask) (((comb) & (mask)) != (mask))

    // Port A checks
    // N/A

    // Port D checks
    // N/A

    // Port B
    #define GPIO_B_COMB                                                                         \
        (SWITCH_INPUT_PIN_MASK ^ STATUS_OUTPUT_PIN_MASK ^ TWO_PULSES_TEST_OUTPUT_PIN_NO0_MASK ^ \
         TWO_PULSES_TEST_OUTPUT_PIN_NO1_MASK)

    #if CHECK_OVERLAP(GPIO_B_COMB, SWITCH_INPUT_PIN_MASK) ||               \
        CHECK_OVERLAP(GPIO_B_COMB, STATUS_OUTPUT_PIN_MASK) ||              \
        CHECK_OVERLAP(GPIO_B_COMB, TWO_PULSES_TEST_OUTPUT_PIN_NO0_MASK) || \
        CHECK_OVERLAP(GPIO_B_COMB, TWO_PULSES_TEST_OUTPUT_PIN_NO1_MASK)
        #error "GPIO_B pin overlapped"
    #endif // GPIO_B_COMB checks

    // Port C
    #define GPIO_C_COMB (RUNT_PULSE_TEST_OUTPUT_PIN_MASK)

    #if CHECK_OVERLAP(GPIO_C_COMB, RUNT_PULSE_TEST_OUTPUT_PIN_MASK)
        #error "GPIO_C pin overlapped"
    #endif // GPIO_C_COMB checks
}
#endif // defined(DEBUG)

void hw_init()
{
    // ===========================================
    // Outputs
    // Make digital, analog and status led pins as output and clear them
    // ===========================================
    HAL_IO_MAKE_OUTPUT (DIGITAL_OUTPUT_GPIO, DIGITAL_OUTPUT_PIN_MASK);
    HAL_IO_OUT_LOW (DIGITAL_OUTPUT_GPIO, DIGITAL_OUTPUT_PIN_MASK);

    HAL_IO_MAKE_OUTPUT (ANALOG_OUTPUT_GPIO, ANALOG_OUTPUT_PIN_MASK);
    HAL_IO_OUT_LOW (ANALOG_OUTPUT_GPIO, ANALOG_OUTPUT_PIN_MASK);

    HAL_IO_MAKE_OUTPUT (STATUS_OUTPUT_GPIO, STATUS_OUTPUT_PIN_MASK);
    HAL_IO_OUT_LOW (STATUS_OUTPUT_GPIO, STATUS_OUTPUT_PIN_MASK);

    // ===========================================
    // Inputs
    // Make switch pin as input and enable pullup
    // ===========================================
    HAL_IO_MAKE_INPUT_WITH_PULLUP (SWITCH_INPUT_GPIO, SWITCH_INPUT_PIN_MASK);
    hal_interrupt_enable (SWITCH_INPUT_INTERRUPT);

    HAL_INTERRUPT_SET();

    // ===========================================
    // IO & Schematic sanity check
    // ===========================================
#if defined(DEBUG)
    hwspec_sanity_check();
#endif
}

static inline void set_status_led (uint8_t state)
{
    HAL_IO_OUT_WRITE_BITS (STATUS_OUTPUT_GPIO, MODE_LED_VALUE_FROM_TESTMODE (state),
                           STATUS_OUTPUT_PIN_SHIFT, STATUS_OUTPUT_PIN_MASK);
}

__attribute__ ((noreturn)) void fw_main (void)
{
    hw_init();
    mode_reset();

#if !defined(UNITTESTS)
    while (1)
#endif // !defined(UNITTESTS)
    {
        set_status_led (mode_get());
        switch (mode_get()) {
        case TEST_MODE_USART_TEST:
            usart_test();
            break;
        case TEST_MODE_RUNT_PULSE_TEST:
            runt_pulse_test();
            break;
        case TEST_MODE_TWO_PULSES_TEST:
            two_pulses_test();
            break;
        case TEST_MODE_SAWTOOTH_TEST:
            sawtooth_test();
            break;
        case TEST_MODE_TRIANGLE_TEST:
            triangle_test();
            break;
        case TEST_MODE_I2C_TEST:
            i2c_test();
            break;
        default:
            hal_impl_panic();
            break;
        }
    }
}

#if !defined(UNITTESTS)
__attribute__ ((noreturn)) int main (void)
{
    fw_main();
}
#endif // !defined(UNITTESTS)

void hal_impl_panic()
{
    set_status_led (TEST_MODE_ERROR);
#if !defined(UNITTESTS)
    while (1)
        ;
#endif
}
