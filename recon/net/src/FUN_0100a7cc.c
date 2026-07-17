/* net-core FUN_0100a7cc @ 0x100a7cc  (CFG-directed candidate) */

#include <stdint.h>
extern int FUN_0102a1e2(void *state);
extern int FUN_01008d00(uint32_t group, uint32_t line);
void FUN_0100a7cc(void)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21000bf4u;
    int status = FUN_0102a1e2((void *)state);
    if (status != 0) {
        status = FUN_01008d00(0x1du, 0x30u);
    }
    state[1] = (uint8_t)status;
}
