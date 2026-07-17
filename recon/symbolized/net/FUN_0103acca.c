#include "g1_net_symbols.h"
/* net-core FUN_0103acca @ 0x103acca  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

void FUN_0103acca(int32_t *param_1)
{
    __DMB();

    int32_t base = *(volatile int32_t *)param_1;
    uint32_t flags = *(volatile uint32_t *)(base + 0x10);
    int32_t iVar1 = *(volatile int32_t *)(base + 0x18);
    int take_ad0e = 0;

    if (flags & 0x20000000) {
        if (iVar1 == 1) {
            int32_t p7 = *(volatile int32_t *)((int8_t *)param_1 + 0x1c);
            uint16_t v1 = *(volatile uint16_t *)(p7);
            if ((int32_t)((uint32_t)v1 << 0x1f) >= 0) {
                take_ad0e = 1;
            }
        }
    } else {
        if (iVar1 == 1) {
            int32_t p8 = *(volatile int32_t *)((int8_t *)param_1 + 0x20);
            int32_t p7 = *(volatile int32_t *)((int8_t *)param_1 + 0x1c);
            int32_t p5 = *(volatile int32_t *)((int8_t *)param_1 + 0x14);
            uint16_t a = *(volatile uint16_t *)(p8 + 2);
            int32_t addr2 = p7 + (p5 << 1);
            uint16_t b = *(volatile uint16_t *)(addr2 + 4);
            uint16_t r3 = (uint16_t)((uint16_t)(a - 1) - b);
            uint16_t r2 = *(volatile uint16_t *)((int8_t *)param_1 + 0x26);
            if (r2 > r3) take_ad0e = 1;
        }
    }

    if (take_ad0e) {
        int32_t f = *(volatile int32_t *)((int8_t *)param_1 + 0x10);
        if (f != 0) {
            void (*fn)(int32_t *) = (void (*)(int32_t *))f;
            fn(param_1);
        }
    }
    *(volatile uint16_t *)((int8_t *)param_1 + 0x26) = 0;
}
