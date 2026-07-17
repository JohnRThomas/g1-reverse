#include "g1_net_symbols.h"
/* net-core FUN_0100ff4a @ 0x100ff4a  (parity 300 trials PROVEN) */

extern void FUN_0100f7b0(void);

unsigned int FUN_0100ff4a(int param_1)
{
    FUN_0100f7b0();
    *(volatile unsigned char *)(*(int *)(param_1 + 4) + 0xc6) = 0x1d;
    return 0;
}
