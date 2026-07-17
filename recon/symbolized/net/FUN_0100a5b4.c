#include "g1_net_symbols.h"
/* net-core FUN_0100a5b4 @ 0x100a5b4  (parity 300 trials PROVEN) */

unsigned char FUN_0100a5b4(void)
{
    volatile unsigned char * const p = (volatile unsigned char * const)((unsigned long)&g_sdc_last_cfg_param3) /*=0x21000bc9*/;
    return *p;
}
