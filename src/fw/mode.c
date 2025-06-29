#include <main.h>
#include <stdbool.h>

static volatile TestModes currentMode;
static volatile bool modeIsDirty;

void mode_advance()
{
    if (++currentMode >= TEST_MODE_COUNT) {
        currentMode = TEST_MODE_USART_TEST;
    }
    modeIsDirty = true;
}

TestModes mode_get()
{
    modeIsDirty = false;
    return currentMode;
}

bool mode_is_dirty()
{
    return modeIsDirty;
}

void mode_reset()
{
    modeIsDirty = false;
    currentMode = TEST_MODE_USART_TEST;
}
