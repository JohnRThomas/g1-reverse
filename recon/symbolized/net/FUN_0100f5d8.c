#include "g1_net_symbols.h"
/* net-core FUN_0100f5d8 @ 0x100f5d8  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01009204(volatile uint32_t *a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);

void FUN_0100f5d8(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    volatile uint32_t * const puVar2 = (uint32_t *)((unsigned long)&g_net_prng_state) /*=0x21000ef4*/;
    uint32_t uVar6 = param_4;
    uint32_t uVar1, uVar3, uVar4, uVar5;

    do {
        FUN_01009204(puVar2, 8, param_3, param_4, uVar6);
        param_4 = puVar2[0];
        param_3 = puVar2[1];
    } while (param_4 == 0 && param_3 == 0);

    do {
        param_3 = param_3 ^ param_4;
        uVar3 = param_3 ^ ((param_4 >> 6) | (param_4 << 0x1a));
        uVar4 = uVar3 ^ (param_3 << 9);
        uVar6 = (((0x9e3779bbu * param_4) >> 0x1b) | ((0x9e3779bbu * param_4) << 5)) * 5;
        uVar5 = uVar4 ^ ((param_3 >> 0x13) | (param_3 << 0xd));
        uVar1 = (((0x9e3779bbu * uVar4) >> 0x1b) | ((0x9e3779bbu * uVar4) << 5)) * 5;
        param_3 = (uVar5 >> 0x13) | (uVar5 << 0xd);
        param_4 = uVar5 ^ ((uVar4 >> 6) | (uVar3 << 0x1a)) ^ (uVar5 << 9);
    } while (uVar1 == 0 && uVar6 == 0);

    puVar2[0] = param_4;
    puVar2[1] = param_3;
    puVar2[2] = uVar6;
    puVar2[3] = uVar1;
}
