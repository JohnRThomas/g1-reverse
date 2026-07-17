/* net-core FUN_010091a8 @ 0x010091a8 */
#include <stdint.h>

extern void thunk_FUN_0101621c(void);

uint32_t FUN_010091a8(void)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21000a30u;
    if (state[0x2d] == 0 && state[0x2c] == 0) {
        thunk_FUN_0101621c();
        return 0;
    }
    return UINT32_MAX;
}
