#include "g1_net_symbols.h"
/* net-core FUN_0102fbd0 @ 0x102fbd0  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int32_t FUN_0102e284(uint32_t a, uint32_t b, void *c, uint32_t d);
extern void FUN_01030014(int32_t a, uint32_t b);
extern int32_t FUN_0103a44c(uint32_t a);

int32_t FUN_0102fbd0(uint32_t param_1)
{
    int32_t iVar1;

    if ((param_1 < 6) && (((int32_t)((0x2aU >> (param_1 & 0xff)) << 0x1f)) < 0)) {
        iVar1 = FUN_0103a44c(((uintptr_t)&g_net_bufpool_evtpool) /*=0x210009fc*/);
        if (iVar1 != 0) {
            FUN_01030014(iVar1 + 0xc, 1);
            *(volatile int8_t *)(iVar1 + 0x18) = (int8_t)param_1;
        }
    } else {
        uint32_t local_20 = 3;
        uint32_t local_1c = "t not fulfilled.\r\n" /*=0x103ddb9*/;
        uint32_t uStack_18 = param_1;
        FUN_0102e284(((uintptr_t)&rodata_103c024) /*=0x103c024*/, 0x1840, &local_20, 0);
        (void)local_1c; (void)uStack_18;
        iVar1 = 0;
    }
    return iVar1;
}

