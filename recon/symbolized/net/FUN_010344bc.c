#include "g1_net_symbols.h"
/* net-core FUN_010344bc @ 0x10344bc  (parity 300 trials PROVEN) */

extern int FUN_010344a8(void);
#define DAT_010344d0 ((unsigned int)((unsigned long)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/)

unsigned short FUN_010344bc(void)
{
    int iVar1 = FUN_010344a8();
    return *(volatile unsigned short *)(DAT_010344d0 + (iVar1 + 8) * 2) & 1;
}
