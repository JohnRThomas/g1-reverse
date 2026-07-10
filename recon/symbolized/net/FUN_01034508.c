#include "g1_net_symbols.h"
/* net-core FUN_01034508 @ 0x1034508  (parity 300 trials PROVEN) */

extern int FUN_010344a8(void);
#define DAT_0103451c ((unsigned int)((uintptr_t)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/)

unsigned int FUN_01034508(void)
{
    int iVar1 = FUN_010344a8();
    unsigned short v = *(volatile unsigned short *)(DAT_0103451c + (iVar1 + 8) * 2);
    return (v >> 1) & 1;
}

