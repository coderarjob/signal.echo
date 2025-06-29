#define YUKTI_TEST_IMPLEMENTATION
#include <yukti.h>
#include <stdbool.h>
#include <utils.h>

YT_TESTP (utils, high8_16bits, int, int)
{
    int input = YT_ARG_0();
    int exp   = YT_ARG_1();

    YT_EQ_SCALAR (HIGH8_16BITS (input), exp);

    YT_END();
}

YT_TESTP (utils, high8_32bits, int, int)
{
    int input = YT_ARG_0();
    int exp   = YT_ARG_1();

    YT_EQ_SCALAR (HIGH8_32BITS (input), exp);

    YT_END();
}

YT_TESTP (utils, low8, int, int)
{
    int input = YT_ARG_0();
    int exp   = YT_ARG_1();

    YT_EQ_SCALAR (LOW8 (input), exp);
    YT_END();
}

YT_TESTP (utils, bits_clear_mask, int, int, int)
{
    int data = YT_ARG_0();
    int mask = YT_ARG_1();
    int exp  = YT_ARG_2();

    BIT_CLEAR_MASK (data, mask);
    YT_EQ_SCALAR (data, exp);

    YT_END();
}

YT_TESTP (utils, bits_set_mask, int, int, int)
{
    int data = YT_ARG_0();
    int mask = YT_ARG_1();
    int exp  = YT_ARG_2();

    BIT_SET_MASK (data, mask);
    YT_EQ_SCALAR (data, exp);

    YT_END();
}

YT_TESTP (utils, is_bit_set_mask, int, int, bool)
{
    int data      = YT_ARG_0();
    int bit_index = YT_ARG_1();
    int exp       = YT_ARG_2();

    YT_EQ_SCALAR (IS_BIT_SET_MASK (data, (1 << bit_index)), (int)exp);
    YT_EQ_SCALAR (IS_BIT_SET (data, bit_index), (int)exp);
    // data remains unchanged after this
    YT_EQ_SCALAR (data, YT_ARG_0());

    YT_END();
}

YT_TESTP (utils, bits_clear, int, int, int)
{
    uint32_t data      = YT_ARG_0();
    uint32_t bit_index = YT_ARG_1();
    uint32_t exp       = YT_ARG_2();

    BIT_CLEAR (data, bit_index);
    YT_EQ_SCALAR (data, exp);

    YT_END();
}

YT_TESTP (utils, bits_set, int, size_t, int*, int)
{
    uint32_t data            = YT_ARG_0();
    size_t bit_indices_count = YT_ARG_1();
    int* bit_index           = YT_ARG_2();
    uint32_t exp             = YT_ARG_3();

    for (size_t i = 0; i < bit_indices_count; i++) {
        BIT_SET (data, bit_index[i]);
    }
    YT_EQ_SCALAR (data, exp);

    YT_END();
}

YT_TESTP (utils, bit_mask_creation, int, int, int)
{
    uint32_t mask_start_bit = YT_ARG_0();
    uint32_t mask_bit_len   = YT_ARG_1();
    uint32_t exp            = YT_ARG_2();

    YT_EQ_SCALAR (BIT_MASK (mask_start_bit, mask_bit_len), (int)exp);
    YT_END();
}

void reset()
{
}

int main (void)
{
    YT_INIT();

    // clang-format off
    high8_16bits (5, YT_ARG (int){ 0xFA13, 0x13FA, 0x13, 0x00, 0xFFFF }, // 16 bit data
                     YT_ARG (int){ 0xFA, 0x0013, 0x00, 0x00, 0x00FF });  // high byte

    high8_32bits (3, YT_ARG (int){ 0x13, 0x00, 0x12345678 },  // 32 bit data
                     YT_ARG (int){ 0x00, 0x00, 0x00000012 }); // high byte

    low8 (6, YT_ARG (int){ 0xFA13, 0x13FA, 0x13, 0x00, 0xFFFF, 0x12345678 },  // data
             YT_ARG (int){ 0x0013, 0x00FA, 0x13, 0x00, 0x00FF, 0x00000078 }); // low byte

    bits_clear_mask (3, YT_ARG (int){ 0xFFFF0000, 0xFFFF0000, 0xFF },  // data
                        YT_ARG (int){ 0xFFFF0000, 0xFF000000, 0x01 },  // clear mask
                        YT_ARG (int){ 0x00000000, 0x00FF0000, 0xFE }); // outcome

    bits_set_mask (3, YT_ARG (int){ 0xFFFF0000, 0x00FF00, 0xFE },    // data
                      YT_ARG (int){ 0xFFFF0000, 0xFF0000, 0x01 },    // mask
                      YT_ARG (int){ 0xFFFF0000, 0xFFFF00, 0xFF });   // outcome

    is_bit_set_mask(4, YT_ARG(int) {0xFFFF0000, 0xFFFF0000, 0xFFFF0000, 0xFFFF0000}, // data
                       YT_ARG(int){0, 15, 24, 31},                                   // bit pos
                       YT_ARG(bool){false, false, true, true});                      // is bit set

    bits_clear(3, YT_ARG(int){0xFFFF0000, 0xF0, 0xFF},   // data
                  YT_ARG(int){31, 0, 0},                 // bit positions
                  YT_ARG(int){0x7FFF0000, 0xF0, 0xFE}); // outcome

    bits_set(3, YT_ARG(int){0xFFFF0000,0xFF00,0xFE},          // data
                YT_ARG(size_t){1,2,1},                        // num of bit positions in below array
                YT_ARG(int*){YT_ARG_SUB_ARRAY(int, {31   }),  // bit positions
                             YT_ARG_SUB_ARRAY(int, {16, 4}),
                             YT_ARG_SUB_ARRAY(int, {0    })},
                YT_ARG(int){0xFFFF0000,0x1FF10,0xFF});        // outcome

    bit_mask_creation(6, YT_ARG(int) {0,    0,   0,   1,   2,    3},    // mask start bit position
                         YT_ARG(int) {2,    6,   3,   2,   6,    3},    // mask bit length
                         YT_ARG(int) {0x3,0x3F,0x7, 0x6, 0xFC, 0x38});  // resulting mask
    // clang-format on
    YT_RETURN_WITH_REPORT();
}
