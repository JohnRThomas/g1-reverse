#include "g1_net_symbols.h"
/* net-core FUN_01024ad0 @ 0x1024ad0  (parity 300 trials PROVEN) */

#define DAT_01024ae8 ((unsigned int)REG_41005000 /*=0x41005000*/)
#define DAT_01024aec ((volatile unsigned char *)((unsigned long)&g_net_radio_timer_active_flag) /*=0x21001bf7*/)

unsigned char FUN_01024ad0(void)
{
    unsigned char bVar1;
    if (*(volatile int *)(DAT_01024ae8 + 0x100) == 0) {
        bVar1 = *DAT_01024aec;
    } else {
        bVar1 = 1;
    }
    return bVar1 & 1;
}
