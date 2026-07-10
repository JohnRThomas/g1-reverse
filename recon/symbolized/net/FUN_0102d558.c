#include "g1_net_symbols.h"
/* net-core FUN_0102d558 @ 0x102d558  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01039e52(void);

typedef int32_t (*fnptr_t)(void);

int32_t FUN_0102d558(int32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4)
{
    int32_t r3;

    if (param_1 == 0) {
        FUN_01039e52();
        return (int32_t)0xffffffea;
    }
    if (*(volatile int32_t **)(param_1 + 8) == 0) {
        FUN_01039e52();
        return (int32_t)0xfffffffb;
    }
    r3 = **(volatile int32_t **)(param_1 + 8);
    if (r3 != 0) {
        fnptr_t f = (fnptr_t)r3;
        return f();
    }
    return 0;
}

