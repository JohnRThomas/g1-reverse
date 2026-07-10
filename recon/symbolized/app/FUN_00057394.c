#include "g1_app_symbols.h"
/* named: FUN_00057394 */
/* Reconstructed FUN_00057394 @ 0x57394  (parity: 300/300 trials, PROVEN) */

void FUN_00057394(void)
{
    unsigned char v = *(volatile unsigned char*)((uintptr_t)&g_smp_pairing_event_cnt) /*=0x2001d531*/;
    v = v + 1;
    if (v < 1) v = 1;
    *(volatile unsigned char*)((uintptr_t)&g_smp_pairing_event_cnt) /*=0x2001d531*/ = v;
}

