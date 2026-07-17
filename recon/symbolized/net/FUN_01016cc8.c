#include "g1_net_symbols.h"
/* net-core FUN_01016cc8 @ 0x1016cc8  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01016828(void);
extern int32_t FUN_01019aa0(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                             uint32_t e, uint32_t f, uint32_t g, uint32_t h);
extern void FUN_01019660(void);

void FUN_01016cc8(uint32_t param_1, uint32_t param_2)
{
    volatile int8_t * const p1 = (int8_t *)((unsigned long)&g_net_ble_pending_channel_idx) /*=0x2100001c*/;
    int8_t cVar1 = *p1;

    if (cVar1 == 0x7f) {
        FUN_01016828();
        return;
    }

    *p1 = 0x7f;
    volatile uint8_t * const state = (uint8_t *)0x21000f90;
    uint32_t mode_arg = state[0x70] == 5 ? 0 : (state[0x70] == 8 ? 3 : 1);
    int32_t iVar2 = FUN_01019aa0(param_1, param_2,
                                 0x21000fd6, state[0xb9],
                                 state[0x8f], state[0x79],
                                 (uint32_t)(int32_t)cVar1, mode_arg);
    if (iVar2 != 0) {
        FUN_01019660();
    }
}
