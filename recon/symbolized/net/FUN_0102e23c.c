#include "g1_net_symbols.h"
/* net-core FUN_0102e23c @ 0x102e23c  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01039bb0(uint32_t a, uint32_t b);
extern void FUN_01039bbe(uint32_t a, uint32_t b, uint32_t c);
extern void FUN_0102ddf4(void);

void FUN_0102e23c(int32_t param_1, uint32_t param_2, uint8_t param_3)
{
    int32_t t;
    uint8_t r3;
    int32_t r4;
    int32_t r3w;

    t = param_1 - ((uintptr_t)&rodata_103c0ec) /*=0x103c0ec*/;
    t = t >> 4;
    t = t + 1;
    r3 = (uint8_t)t;

    if (param_1 == 0) {
        FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, "t_hci_raw" /*=0x103d635*/, 0xdf);
        FUN_01039bb0("t_hci_raw" /*=0x103d635*/, 0xdf);
    }

    r4 = *(volatile int32_t *)(param_1 + 4);
    *(volatile uint8_t *)(r4 + 4) = r3;
    r3w = *(volatile int32_t *)(param_1 + 4);
    *(volatile uint8_t *)(r3w + 6) = param_3;
    r3w = *(volatile int32_t *)(param_1 + 4);
    *(volatile uint32_t *)(r3w) = param_2;
    r3w = *(volatile int32_t *)(param_1 + 4);
    *(volatile uint8_t *)(r3w + 5) = 1;

    FUN_0102ddf4();
}

