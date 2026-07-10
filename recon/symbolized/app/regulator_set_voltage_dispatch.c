#include "g1_app_symbols.h"
/* named: regulator_set_voltage_dispatch */
/* Reconstructed regulator_set_voltage_dispatch @ 0x84348  (parity: 300/300 trials, PROVEN) */

extern int FUN_000842cc(int,int,int,int);
extern int regulator_set_voltage_range(int,int,int);

int regulator_set_voltage_dispatch(int param_1, int param_2, int param_3)
{
    int iVar1 = *(int*)(param_1+4);
    unsigned char sel = *(unsigned char*)(iVar1+0x20);
    int uVar2;
    switch(sel) {
    case 0: uVar2=0; break;
    case 1: uVar2=1; break;
    case 2: uVar2=0; return FUN_000842cc(iVar1,uVar2,param_2,param_3);
    case 3: uVar2=1; return FUN_000842cc(iVar1,uVar2,param_2,param_3);
    default: return 0xffffffed;
    }
    return regulator_set_voltage_range(iVar1,uVar2,param_2);
}

