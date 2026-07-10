#include "g1_app_symbols.h"
/* named: img_mgmt_ver_str */
/* Reconstructed img_mgmt_ver_str @ 0x51f88  (parity: 300/300 trials, PROVEN) */

extern int FUN_00077914(int, int, unsigned int, unsigned int, unsigned int, unsigned int);

int img_mgmt_ver_str(unsigned char *param_1, int param_2)
{
    unsigned int uVar2 = *(volatile unsigned short*)(param_1 + 2);
    unsigned int uVar3 = *(volatile unsigned char*)(param_1 + 1);
    unsigned char p0 = *(volatile unsigned char*)(param_1 + 0);
    int iVar1 = FUN_00077914(param_2, 0x19, "%hu.%hu.%hu" /*=0xf27cf*/, p0, uVar3, uVar2);
    int iVar4 = *(volatile int*)(param_1 + 4);
    if (iVar4 != 0) {
        iVar4 = FUN_00077914(param_2 + iVar1, 0x19 - iVar1, ".%u" /*=0xf27db*/, iVar4, uVar3, uVar2);
    }
    return iVar1 + iVar4;
}

