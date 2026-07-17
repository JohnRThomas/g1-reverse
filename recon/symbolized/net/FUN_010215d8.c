#include "g1_net_symbols.h"
/* net-core FUN_010215d8 @ 0x10215d8  (parity 300 trials PROVEN) */

extern unsigned int FUN_010209f0(unsigned int);
#define DAT_010215f0 ((unsigned int)0x10624dd3)

int FUN_010215d8(int param_1, unsigned int param_2)
{
    unsigned int uVar1 = FUN_010209f0(param_2);
    unsigned long long prod = (unsigned long long)DAT_010215f0 * (unsigned long long)uVar1;
    return param_1 - (unsigned int)(prod >> 0x26);
}
