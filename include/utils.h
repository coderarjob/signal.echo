#pragma once

#define HIGH8(v)                    ((v >> 8) & 0xFF)
#define LOW8(v)                     (v & 0xFF)

#define BIT_CLEAR_MASK(port, mask)  ((port) &= ~(mask))
#define BIT_SET_MASK(port, mask)    ((port) |= (mask))
#define IS_BIT_SET_MASK(port, mask) ((port) &= (mask))

#define BIT_CLEAR(port, pin)        BIT_CLEAR_MASK (port, 1 << (pin))
#define BIT_SET(port, pin)          BIT_SET_MASK (port, 1 << (pin))
#define IS_BIT_SET(port, pin)       IS_BIT_SET_MASK (port, 1 << (pin))
