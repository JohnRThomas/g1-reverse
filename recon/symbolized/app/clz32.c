#include "g1_app_symbols.h"
/* named: clz32 */
/* Reconstructed clz32 @ 0x87510  (parity: 300/300 trials, PROVEN) */

int clz32(unsigned int param_1)
{
    int iVar1;
    if (param_1 < ((uintptr_t)&tbl_ffc8) /*=0x10000*/) {
        param_1 = param_1 << 0x10;
        iVar1 = 0x10;
    } else {
        iVar1 = 0;
    }
    if (param_1 < 0x1000000) {
        param_1 = param_1 << 8;
        iVar1 = iVar1 + 8;
    }
    if (param_1 < 0x10000000) {
        param_1 = param_1 << 4;
        iVar1 = iVar1 + 4;
    }
    if (param_1 < 0x40000000) {
        if ((int)(param_1 << 2) < 0) return iVar1 + 2;
        if ((int)(param_1 << 3) < 0) return iVar1 + 3;
        iVar1 = 0x20;
    } else if ((int)param_1 >= 0) {
        return iVar1 + 1;
    }
    return iVar1;
}

