#include "g1_net_symbols.h"
/* net-core FUN_0102a4b0 @ 0x102a4b0  (parity 300 trials PROVEN) */

extern void FUN_01036824(int);
void FUN_0102a4b0(void)
{
    volatile int * const * const p = (volatile int * const * const)((unsigned long)&g_sdc_hci_transport_obj) /*=0x210045f4*/;
    int base = *(int*)*p;
    if (*(int*)(base + 0x2c) == 0) {
        FUN_01036824(base + 0x24);
    }
}
