/* net-core FUN_01029b24 @ 0x1029b24  (CFG-directed candidate) */
#include <stdint.h>
int32_t FUN_01029b24(const volatile uint8_t *state)
{
    uint32_t mode = state[0x10];
    if (mode == 0u || mode == 1u)
        return 0;
    return mode == 7u ? 0 : 1;
}
