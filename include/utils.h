#pragma once

#define HIGH8_16BITS(v)               ((v >> 8) & 0xFF)
#define HIGH8_32BITS(v)               ((v >> 24) & 0xFF)
#define LOW8(v)                       (v & 0xFF)

#define BIT_CLEAR_MASK(data, mask)    ((data) &= ~(mask))
#define BIT_SET_MASK(data, mask)      ((data) |= (mask))
#define IS_BIT_SET_MASK(data, mask)   (((data) & (mask)) != 0)

#define BIT_CLEAR(data, bit)          BIT_CLEAR_MASK (data, 1 << (bit))
#define BIT_SET(data, bit)            BIT_SET_MASK (data, 1 << (bit))
#define IS_BIT_SET(data, bit)         IS_BIT_SET_MASK (data, 1 << (bit))

#define BIT_MASK(start_bit, num_bits) (((1 << num_bits) - 1) << start_bit)
