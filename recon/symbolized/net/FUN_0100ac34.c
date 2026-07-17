#include "g1_net_symbols.h"
/* net-core FUN_0100ac34 @ 0x100ac34 */
#include <stdint.h>

extern void FUN_01020500(void);
extern void FUN_0101ff4c(void);
extern void FUN_0100efc8(void *, const void *, unsigned);

void FUN_0100ac34(void)
{
    volatile uint8_t *const state = (volatile uint8_t *)((unsigned long)&g_net_radio_drv_ctx) /*=0x21000c48*/;
    FUN_01020500();
    FUN_0101ff4c();
    ((void (*)(uint16_t, unsigned))*(volatile uintptr_t *)(state + 0x34))(
        *(volatile uint16_t *)(state + 0x30), 0);
    if (state[0x18] != 0) {
        *(volatile uint32_t *)(state + 0x0c) = *(volatile uint32_t *)(state + 0x00);
        *(volatile uint32_t *)(state + 0x10) = *(volatile uint32_t *)(state + 0x04);
        *(volatile uint32_t *)(state + 0x14) = *(volatile uint32_t *)(state + 0x08);
        FUN_0100efc8((void *)(state + 0x19), (const void *)0x0100b381U, 2);
    }
    ((void (*)(uint8_t, uint8_t))*(volatile uintptr_t *)(state + 0x40))(
        state[0x3e], state[0x3d]);
    state[0x44] = 0;
}
