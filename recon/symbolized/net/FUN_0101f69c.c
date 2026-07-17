#include "g1_net_symbols.h"
/* net-core FUN_0101f69c @ 0x101f69c  (parity 300 trials PROVEN) */

extern void FUN_0101f894(int);
extern void FUN_010161e8(void);
#define DAT_0101f6b0 ((unsigned int)((unsigned long)&g_net_ble_conn_role_cfg) /*=0x21001208*/)
#define DAT_0101f6b4 ((unsigned int)((unsigned long)&rodata_101ec69) /*=0x101ec69*/)

void FUN_0101f69c(void)
{
    FUN_0101f894(5);
    FUN_010161e8();
    *(volatile unsigned int *)(DAT_0101f6b0 + 0x24) = DAT_0101f6b4;
    return;
}
