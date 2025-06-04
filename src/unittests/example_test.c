#include <stdbool.h>
#define YUKTI_TEST_IMPLEMENTATION
#include "../include/yukti.h"

YT_TEST(example, always_pass)
{
    YT_EQ_SCALAR(true, true);
    YT_END();
}

void reset()
{
}

int main(void) {
    always_pass();
    return 0;
}
