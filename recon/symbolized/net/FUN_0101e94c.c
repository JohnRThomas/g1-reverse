#include "g1_net_symbols.h"
/* net-core FUN_0101e94c @ 0x101e94c  (parity 300 trials PROVEN) */

extern void FUN_0100d738(void);
extern unsigned char FUN_010283fe(void);
void FUN_0101e94c(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)((unsigned long)&g_net_ble_conn_role_cfg) /*=0x21001208*/;
    unsigned char uVar1;
    FUN_0100d738();
    uVar1 = FUN_010283fe();
    p[0x1c] = uVar1;
}
