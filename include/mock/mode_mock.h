#pragma once
#include <main.h>
#include <yukti.h>

YT_DECLARE_FUNC_VOID (mode_advance);
YT_DECLARE_FUNC_VOID (mode_reset);
YT_DECLARE_FUNC (TestModes, mode_get);
YT_DECLARE_FUNC (bool, mode_is_dirty);

YT_DEFINE_FUNC_VOID (mode_advance);
YT_DEFINE_FUNC_VOID (mode_reset);
YT_DEFINE_FUNC (TestModes, mode_get);
YT_DEFINE_FUNC (bool, mode_is_dirty);

void reset_mode_mocks()
{
    YT_RESET_MOCK (mode_advance);
    YT_RESET_MOCK (mode_reset);
    YT_RESET_MOCK (mode_get);
    YT_RESET_MOCK (mode_is_dirty);
}
