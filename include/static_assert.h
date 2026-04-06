#pragma once

#define NDU__STATIC_ASSERT2(m, t) \
    __attribute__ ((unused)) typedef char static_assert_##m[(t) ? 1 : -1]
#define NDU__STATIC_ASSERT(m, t) NDU__STATIC_ASSERT2 (m, t)
#define STATIC_ASSERT(t)         NDU__STATIC_ASSERT (__LINE__, t)
