#include "g1_net_symbols.h"
/* net-core FUN_01021694 @ 0x1021694  (parity 300 trials PROVEN) */

extern int FUN_010209f0(unsigned int a);
extern int FUN_010209e0(int a, int b, int c, int d);

int FUN_01021694(int param_1, unsigned int param_2, int param_3)
{
    int iVar2;
    unsigned long long lVar1;
    int val;
    unsigned int inner;
    iVar2 = FUN_010209f0(param_2);
    val = *(volatile int *)(((unsigned long)&rodata_103c5c4) /*=0x103c5c4*/ + param_3*4 + 0x14);
    inner = (unsigned int)(param_1*1000 + val + 2999 - iVar2);
    lVar1 = (unsigned long long)0x10624dd3UL * (unsigned long long)inner;
    iVar2 = FUN_010209e0(param_3, 1000, iVar2, (int)lVar1);
    return iVar2 + 5 + (unsigned int)(lVar1 >> 0x26);
}
