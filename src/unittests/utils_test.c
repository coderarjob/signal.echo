#include <utils.h>
#define YUKTI_TEST_IMPLEMENTATION
#include <yukti.h>

YT_TEST (utils, high8)
{
    YT_EQ_SCALAR (HIGH8_16BITS (0xFA13), 0xFA);
    YT_EQ_SCALAR (HIGH8_16BITS (0x13FA), 0x13);
    YT_EQ_SCALAR (HIGH8_16BITS (0x13), 0x00);
    YT_EQ_SCALAR (HIGH8_16BITS (0x00), 0x00);
    YT_EQ_SCALAR (HIGH8_16BITS (0xFFFF), 0xFF);
    YT_EQ_SCALAR (HIGH8_32BITS (0x12345678), 0x12);

    YT_END();
}

YT_TEST (utils, low8)
{
    YT_EQ_SCALAR (LOW8 (0xFA13), 0x13);
    YT_EQ_SCALAR (LOW8 (0x13FA), 0xFA);
    YT_EQ_SCALAR (LOW8 (0x13), 0x13);
    YT_EQ_SCALAR (LOW8 (0x00), 0x00);
    YT_EQ_SCALAR (LOW8 (0xFFFF), 0xFF);
    YT_EQ_SCALAR (LOW8 (0x123456), 0x56);
    YT_END();
}

YT_TEST (utils, bits_clear_mask)
{
    uint32_t v1 = 0xFFFF0000;
    BIT_CLEAR_MASK (v1, v1);
    YT_EQ_SCALAR (v1, 0x0);

    uint32_t v2 = 0xFFFF0000;
    BIT_CLEAR_MASK (v2, 0xFF000000);
    YT_EQ_SCALAR (v2, 0xFF0000);

    uint32_t v3 = 0xFF;
    BIT_CLEAR_MASK (v3, 0x1);
    YT_EQ_SCALAR (v3, 0xFE);

    YT_END();
}

YT_TEST (utils, bits_set_mask)
{
    uint32_t v1 = 0xFFFF0000;
    BIT_SET_MASK (v1, v1);
    YT_EQ_SCALAR (v1, v1);

    uint32_t v2 = 0xFF00;
    BIT_SET_MASK (v2, 0xFF0000);
    YT_EQ_SCALAR (v2, 0xFFFF00);

    uint32_t v3 = 0xFE;
    BIT_SET_MASK (v3, 0x1);
    YT_EQ_SCALAR (v3, 0xFF);

    YT_END();
}

YT_TEST (utils, is_bit_set_mask)
{
    uint32_t v1 = 0xFFFF0000;

    YT_EQ_SCALAR (IS_BIT_SET_MASK (v1, (1 << 0)), 0);
    YT_EQ_SCALAR (IS_BIT_SET_MASK (v1, (1 << 15)), 0);
    YT_EQ_SCALAR (IS_BIT_SET_MASK (v1, (1 << 24)), 1);
    YT_EQ_SCALAR (IS_BIT_SET_MASK (v1, (1 << 31)), 1);

    // v1 remains unchanged after this
    YT_EQ_SCALAR (v1, 0xFFFF0000);

    YT_END();
}

YT_TEST (utils, bits_clear)
{
    uint32_t v1 = 0xFFFF0000;
    BIT_CLEAR (v1, 31);
    YT_EQ_SCALAR (v1, 0x7FFF0000);

    uint32_t v2 = 0xF0;
    BIT_CLEAR (v2, 0);
    YT_EQ_SCALAR (v2, v2);

    uint32_t v3 = 0xFF;
    BIT_CLEAR (v3, 0);
    YT_EQ_SCALAR (v3, 0xFE);

    YT_END();
}

YT_TEST (utils, bits_set)
{
    uint32_t v1 = 0xFFFF0000;
    BIT_SET (v1, 31);
    YT_EQ_SCALAR (v1, v1);

    uint32_t v2 = 0xFF00;
    BIT_SET (v2, 16);
    BIT_SET (v2, 17);
    BIT_SET (v2, 18);
    BIT_SET (v2, 19);
    YT_EQ_SCALAR (v2, 0xFFF00);

    uint32_t v3 = 0xFE;
    BIT_SET (v3, 0);
    YT_EQ_SCALAR (v3, 0xFF);

    YT_END();
}

YT_TEST (utils, is_bit_set)
{
    uint32_t v1 = 0xFFFF0000;

    YT_EQ_SCALAR (IS_BIT_SET (v1, 0), 0);
    YT_EQ_SCALAR (IS_BIT_SET (v1, 15), 0);
    YT_EQ_SCALAR (IS_BIT_SET (v1, 24), 1);
    YT_EQ_SCALAR (IS_BIT_SET (v1, 31), 1);

    // v1 remains unchanged after this
    YT_EQ_SCALAR (v1, 0xFFFF0000);

    YT_END();
}

YT_TEST (utils, bit_mask_creation)
{
    YT_EQ_SCALAR(BIT_MASK(0, 2), 0x3);
    YT_EQ_SCALAR(BIT_MASK(0, 6), 0x3F);
    YT_EQ_SCALAR(BIT_MASK(0, 3), 0x7);

    YT_EQ_SCALAR(BIT_MASK(1, 2), 0x6);
    YT_EQ_SCALAR(BIT_MASK(2, 6), 0xFC);
    YT_EQ_SCALAR(BIT_MASK(3, 3), 0x38);
    YT_END();
}

void reset()
{
}

int main (void)
{
    high8();
    low8();
    bits_clear_mask();
    bits_clear();
    bits_set_mask();
    bits_set();
    is_bit_set_mask();
    is_bit_set();
    bit_mask_creation();
    return 0;
}
