/* net-core FUN_01009184 @ 0x1009184 */
#include <stdint.h>

extern void FUN_010294ba(void);

uint32_t FUN_01009184(void)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21000a30u;

    if (state[0x2d] == 0 && state[0x2c] == 0) {
        FUN_010294ba();
        return 0;
    }
    return UINT32_MAX;
}
