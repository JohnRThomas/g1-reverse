#include "g1_net_symbols.h"
/* net-core FUN_0101dd48 @ 0x101dd48  (parity 157 trials PROVEN) */
#include <stdint.h>

extern void FUN_01008d00(uint32_t a, uint32_t b, uint32_t c, uint32_t d);

void FUN_0101dd48(int32_t param_1, int32_t param_2, uint32_t param_3, uint32_t param_4)
{
    volatile int32_t * const g_head = (int32_t *)((unsigned long)&g_timeout_list) /*=0x2100113c*/;
    int32_t r1;
    int32_t r3;
    uint32_t r2;

    *(int32_t *)(param_1 + 0x1c) = param_2;
    if (param_2 == 0) {
        r3 = *g_head;
        *(int32_t *)(param_1 + 0x18) = r3;
        if (r3 == 0) {
            *g_head = param_1;
            *(int32_t *)(param_1 + 0xc) = 0;
            return;
        }
        *(int32_t *)(r3 + 0x1c) = param_1;
        *g_head = param_1;
        r1 = *(int32_t *)(param_1 + 0x1c);
        goto join_zero_check;
    } else {
        r3 = *(int32_t *)(param_2 + 0x18);
        *(int32_t *)(param_2 + 0x18) = param_1;
        *(int32_t *)(param_1 + 0x18) = r3;
        if (r3 == 0) {
            *(int32_t *)(param_1 + 0xc) = 0;
            r1 = param_2;
            goto merge_point;
        }
        *(int32_t *)(r3 + 0x1c) = param_1;
        r1 = *(int32_t *)(param_1 + 0x1c);
        goto join_zero_check;
    }

join_zero_check:
    *(int32_t *)(param_1 + 0xc) = 0;
    if (r1 == 0) {
        return;
    }
merge_point:
    r3 = *(int32_t *)(r1 + 0xc);
    if (r3 != 0) {
        r2 = *(uint32_t *)(param_1 + 8);
        if ((uint32_t)r3 < r2) {
            FUN_01008d00(0x37, 0x2c, r2, (uint32_t)r3);
            for (;;) {}
        }
        r3 = r3 - r2;
        *(int32_t *)(param_1 + 0xc) = r3;
    }
    *(int32_t *)(r1 + 0xc) = 0;
}
