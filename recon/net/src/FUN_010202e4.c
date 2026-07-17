/* net-core FUN_010202e4 @ 0x010202e4, exact Thumb extent 0x06 bytes. */
#include <stdint.h>

/* Read the controller clock/timestamp word retained at state offset 0x20. */
uint32_t FUN_010202e4(void)
{
    volatile const uint32_t *const controller_state =
        (volatile const uint32_t *)0x21000db0u;
    return controller_state[8];
}
