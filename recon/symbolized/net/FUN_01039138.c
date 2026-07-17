#include "g1_net_symbols.h"
/* net-core FUN_01039138 @ 0x1039138  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_0103b62e(void *dst, uint32_t val, uint32_t len);
extern void FUN_01039190(void *a, uint32_t b, void *c, uint32_t d, void *e);

void FUN_01039138(uint8_t *param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    uint8_t auStack_34[0x1c];
    uint8_t local_32;
    uint32_t local_30;
    uint8_t *local_20;
    uint8_t *local_24;
    uint32_t uStack_4;
    uint32_t uVar1;

    uStack_4 = param_4;
    FUN_0103b62e(auStack_34, 0, 0x1c);
    local_32 = 2;
    local_30 = ((unsigned long)&rodata_103be3f) /*=0x103be3f*/;

    uVar1 = param_2;
    if (param_2 != 0) {
        if (param_2 > 0x7fffffff) {
            uVar1 = 0x80000000;
        }
        uVar1 = uVar1 - 1;
    }
    local_20 = param_1 + uVar1;
    local_24 = param_1;

    FUN_01039190(auStack_34, param_3, &uStack_4, uVar1, &uStack_4);

    if (param_2 != 0) {
        *local_24 = 0;
    }
    (void)local_32; (void)local_30; (void)local_20;
}
