#include "g1_net_symbols.h"
/* net-core FUN_01021838 @ 0x1021838  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01021800(void);
extern void FUN_010217cc(void);

void FUN_01021838(int32_t param_1)
{
    volatile uint8_t * const g = (uint8_t *)((uintptr_t)&g_net_clk_onoff_ctx) /*=0x21001670*/;

    FUN_01021800();
    *(volatile uint8_t *)(param_1 + 0x80) = 0;
    g[10] = g[10] - 1;
    FUN_010217cc();
}

