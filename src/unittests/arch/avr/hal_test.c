#include <arch/avr/hal.h>
#define YUKTI_TEST_IMPLEMENTATION
#define YUKTI_TEST_DEBUG
#include <yukti.h>
#include <utils.h>

/* ====================================================
 * Mocking AVR registers & LIBC functions
 * ====================================================*/
uint8_t porta, ddra, pina;
#define PORTA (*(&porta))
#define DDRA  (*(&ddra))
#define PINA  (*(&pina))

uint8_t portb, ddrb, pinb;
#define PORTB (*(&portb))
#define DDRB  (*(&ddrb))
#define PINB  (*(&pinb))

uint8_t portc, ddrc, pinc;
#define PORTC (*(&portc))
#define DDRC  (*(&ddrc))
#define PINC  (*(&pinc))

uint8_t portd, ddrd, pind;
#define PORTD (*(&portd))
#define DDRD  (*(&ddrd))
#define PIND  (*(&pind))

YT_DECLARE_FUNC_VOID (_delay_loop_2, uint16_t);
YT_DECLARE_FUNC_VOID (sei);
YT_DECLARE_FUNC_VOID (cli);

YT_DEFINE_FUNC_VOID (_delay_loop_2, uint16_t);
YT_DEFINE_FUNC_VOID (sei);
YT_DEFINE_FUNC_VOID (cli);

/* ====================================================
 * Test implementations
 * ====================================================*/
YT_TEST (hal, io_write_byte)
{
    HAL_IO_OUT_WRITE (HAL_GPIO_A, 0x10);
    HAL_IO_OUT_WRITE (HAL_GPIO_B, 0x2D);
    HAL_IO_OUT_WRITE (HAL_GPIO_C, 0x3E);
    HAL_IO_OUT_WRITE (HAL_GPIO_D, 0x4F);
    YT_EQ_SCALAR (porta, 0x10);
    YT_EQ_SCALAR (portb, 0x2D);
    YT_EQ_SCALAR (portc, 0x3E);
    YT_EQ_SCALAR (portd, 0x4F);
    YT_END();
}

YT_TEST (hal, io_read_byte)
{
    pina = 0xA1;
    YT_EQ_SCALAR (HAL_IO_IN_READ (HAL_GPIO_A), 0xA1);
    pinb = 0xB2;
    YT_EQ_SCALAR (HAL_IO_IN_READ (HAL_GPIO_B), 0xB2);
    pinc = 0xC3;
    YT_EQ_SCALAR (HAL_IO_IN_READ (HAL_GPIO_C), 0xC3);
    pind = 0xD4;
    YT_EQ_SCALAR (HAL_IO_IN_READ (HAL_GPIO_D), 0xD4);

    YT_END();
}

YT_TEST (hal, io_write_bits)
{
    porta = 0xFF;
    HAL_IO_OUT_WRITE_BITS (HAL_GPIO_A, 0xB, 0x0, 0xF);
    YT_EQ_SCALAR (porta, 0xFB);

    portb = 0xFF;
    HAL_IO_OUT_WRITE_BITS (HAL_GPIO_B, 0xB, 0x1, (0xF << 1));
    YT_EQ_SCALAR (portb, 0xF7);

    portc = 0xFF;
    HAL_IO_OUT_WRITE_BITS (HAL_GPIO_C, 0x0, 0x4, (0xF << 0x4));
    YT_EQ_SCALAR (portc, 0x0F);

    portd = 0xF0;
    HAL_IO_OUT_WRITE_BITS (HAL_GPIO_D, 0x0, 0x4, (0xF << 0x4));
    YT_EQ_SCALAR (portd, 0x00);

    porta = 0xFF;
    HAL_IO_OUT_WRITE_BITS (HAL_GPIO_A, 0x0, 0x7, (0xF << 0x7));
    YT_EQ_SCALAR (porta, 0x7F);
    YT_END();
}

YT_TEST (hal, io_output_low)
{
    porta = 0xFF;
    HAL_IO_OUT_LOW (HAL_GPIO_A, 0x10);
    YT_EQ_SCALAR (porta, 0xEF);

    portb = 0xF0;
    HAL_IO_OUT_LOW (HAL_GPIO_B, 0x11);
    YT_EQ_SCALAR (portb, 0xE0);

    portc = 0xFF;
    HAL_IO_OUT_LOW (HAL_GPIO_C, 0xF0);
    YT_EQ_SCALAR (portc, 0xF);

    portd = 0xFF;
    HAL_IO_OUT_LOW (HAL_GPIO_D, 0x80);
    YT_EQ_SCALAR (portd, 0x7F);

    YT_END();
}

YT_TEST (hal, io_output_high)
{
    porta = 0xFF;
    HAL_IO_OUT_HIGH (HAL_GPIO_A, 0x10);
    YT_EQ_SCALAR (porta, 0xFF);

    portb = 0xF0;
    HAL_IO_OUT_HIGH (HAL_GPIO_B, 0x11);
    YT_EQ_SCALAR (portb, 0xF1);

    portc = 0x00;
    HAL_IO_OUT_HIGH (HAL_GPIO_C, 0xF1);
    YT_EQ_SCALAR (portc, 0xF1);

    portd = 0x0F;
    HAL_IO_OUT_HIGH (HAL_GPIO_D, 0x81);
    YT_EQ_SCALAR (portd, 0x8F);

    YT_END();
}

YT_TEST (hal, io_make_output)
{
    ddra = 0x00;
    HAL_IO_MAKE_OUTPUT (HAL_GPIO_A, 0x10);
    YT_EQ_SCALAR (ddra, 0x10);

    ddrb = 0xFF;
    HAL_IO_MAKE_OUTPUT (HAL_GPIO_B, 0x10);
    YT_EQ_SCALAR (ddrb, 0xFF);

    ddrc = 0xF0;
    HAL_IO_MAKE_OUTPUT (HAL_GPIO_C, 0x0B);
    YT_EQ_SCALAR (ddrc, 0xFB);

    ddrd = 0x7F;
    HAL_IO_MAKE_OUTPUT (HAL_GPIO_D, 0xE0);
    YT_EQ_SCALAR (ddrd, 0xFF);

    YT_END();
}

YT_TEST (hal, io_make_input_no_pullup)
{
    ddra  = 0x00;
    porta = 0x00;
    HAL_IO_MAKE_INPUT_NO_PULLUP (HAL_GPIO_A, 0x10);
    YT_EQ_SCALAR (ddra, 0x00);
    YT_EQ_SCALAR (porta, 0x00);

    ddrb  = 0xFF;
    portb = 0xFF;
    HAL_IO_MAKE_INPUT_NO_PULLUP (HAL_GPIO_B, 0x10);
    YT_EQ_SCALAR (ddrb, 0xEF);
    YT_EQ_SCALAR (portb, 0xEF);

    ddrc  = 0x1F;
    portc = 0x00;
    HAL_IO_MAKE_INPUT_NO_PULLUP (HAL_GPIO_C, 0x0B);
    YT_EQ_SCALAR (ddrc, 0x14);
    YT_EQ_SCALAR (portc, 0x00);

    ddrd  = 0xEF;
    portd = 0xFF;
    HAL_IO_MAKE_INPUT_NO_PULLUP (HAL_GPIO_D, 0x80);
    YT_EQ_SCALAR (ddrd, 0x6F);
    YT_EQ_SCALAR (portd, 0x7F);
    YT_END();
}

YT_TEST (hal, io_make_input_with_pullup)
{
    ddra  = 0x00;
    porta = 0x00;
    HAL_IO_MAKE_INPUT_WITH_PULLUP (HAL_GPIO_A, 0x10);
    YT_EQ_SCALAR (ddra, 0x00);
    YT_EQ_SCALAR (porta, 0x10);

    ddrb  = 0xFF;
    portb = 0xFF;
    HAL_IO_MAKE_INPUT_WITH_PULLUP (HAL_GPIO_B, 0x10);
    YT_EQ_SCALAR (ddrb, 0xEF);
    YT_EQ_SCALAR (portb, 0xFF);

    ddrc  = 0x1F;
    portc = 0x00;
    HAL_IO_MAKE_INPUT_WITH_PULLUP (HAL_GPIO_C, 0x0B);
    YT_EQ_SCALAR (ddrc, 0x14);
    YT_EQ_SCALAR (portc, 0x0B);

    ddrd  = 0xEF;
    portd = 0xF0;
    HAL_IO_MAKE_INPUT_WITH_PULLUP (HAL_GPIO_D, 0x81);
    YT_EQ_SCALAR (ddrd, 0x6E);
    YT_EQ_SCALAR (portd, 0xF1);
    YT_END();
}

YT_TEST (hal, loop_delay)
{
    YT_MUST_CALL_IN_ORDER (_delay_loop_2, YT_V (0xFF10));
    HAL_LOOP_DELAY (0xFF10);
    YT_EQ_SCALAR (true, true);
    YT_END();
}

YT_TEST (hal, interrupt_set)
{
    YT_MUST_CALL_IN_ORDER (sei);
    HAL_INTERRUPT_SET();
    YT_EQ_SCALAR (true, true);
    YT_END();
}

YT_TEST (hal, interrupt_clear)
{
    YT_MUST_CALL_IN_ORDER (cli);
    HAL_INTERRUPT_CLEAR();
    YT_EQ_SCALAR (true, true);
    YT_END();
}

YT_TEST (hal, baud_counter)
{
#define F_CPU 12E6
    uint16_t counter = HAL_BAUD_COUNTER (10000U);
    YT_EQ_SCALAR (counter, 74);

    counter = HAL_BAUD_COUNTER (9600U);
    YT_EQ_SCALAR (counter, 77);
    YT_END();
}

/* ====================================================
 * reset() & main()
 * ====================================================*/
void reset()
{
    ddra = 0xFF;
    ddrb = 0xFF;
    ddrc = 0xFF;
    ddrd = 0xFF;

    porta = 0xFF;
    portb = 0xFF;
    portc = 0xFF;
    portd = 0xFF;

    pina = 0xFF;
    pinb = 0xFF;
    pinc = 0xFF;
    pind = 0xFF;

    YT_RESET_MOCK (sei);
    YT_RESET_MOCK (cli);
    YT_RESET_MOCK (_delay_loop_2);
}

int main (void)
{
    io_write_byte();
    io_read_byte();
    io_write_bits();
    io_output_low();
    io_output_high();
    io_make_output();
    io_make_input_no_pullup();
    io_make_input_with_pullup();
    loop_delay();
    interrupt_clear();
    interrupt_set();
    baud_counter();
    return 0;
}
