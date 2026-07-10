#include "g1_net_symbols.h"
/* net-core FUN_01034520 @ 0x1034520  (parity 300 trials PROVEN) */

extern int FUN_010344a8(void);
static volatile unsigned short * const DAT_01034534 = (unsigned short *)((uintptr_t)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/;

unsigned short FUN_01034520(void)
{
    int iVar1 = FUN_010344a8();
    return DAT_01034534[iVar1 + 8] >> 0xd;
}

