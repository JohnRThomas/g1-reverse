#include "g1_net_symbols.h"
/* net-core FUN_0102e484 @ 0x102e484  (parity 300 trials PROVEN) */

extern void FUN_0102e460(unsigned int, unsigned int);
void FUN_0102e484(unsigned int param_1, int param_2)
{
    if ((param_2 << 0x1b) < 0) return;
    unsigned int uVar1;
    if ((param_2 << 0x1a) < 0) uVar1 = "tput.c" /*=0x103cf09*/; else uVar1 = ((uintptr_t)&rodata_103e5c9) /*=0x103e5c9*/;
    FUN_0102e460(param_1, uVar1);
}

