#include <main.h>
#include <stdbool.h>

static volatile TestModes currentMode;
static volatile bool modeIsDirty;

void mode_advance()
{
    if (++currentMode >= TEST_COUNT) {
        currentMode = USART_TEST;
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
