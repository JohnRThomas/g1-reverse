#include "g1_net_symbols.h"
/* net-core FUN_010344d4 @ 0x10344d4  (parity 300 trials PROVEN) */

extern int FUN_010344a8(void);
#define DAT_010344e8 ((unsigned int)((uintptr_t)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/)

unsigned int FUN_010344d4(void)
{
    int iVar1 = FUN_010344a8();
    unsigned short v = *(volatile unsigned short *)(DAT_010344e8 + (iVar1 + 8) * 2);
    return (v >> 5) & 1;
}

