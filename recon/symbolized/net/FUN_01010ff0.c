#include "g1_net_symbols.h"
/* net-core FUN_01010ff0 @ 0x1010ff0  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int);
extern int FUN_0100ca98(int, void*, void*);
extern void FUN_0100ef88(void*, unsigned int, unsigned int);

void FUN_01010ff0(unsigned char *param_1, int param_2)
{
    if (param_1[200] != 0) {
        return;
    }
    param_1[0xc9] = param_1[0];
    if (param_2 == 0xff) {
        unsigned char *pbVar2 = *(unsigned char**)((uintptr_t)&g_net_own_addr_info) /*=0x21000f20*/;
        param_1[0xca] = (unsigned char)(((unsigned int)pbVar2[0] << 0x19) >> 0x1f);
        *(unsigned int*)(param_1 + 0xcb) = *(unsigned int*)(pbVar2 + 3);
        *(unsigned short*)(param_1 + 0xcf) = *(unsigned short*)(pbVar2 + 7);
    } else {
        int iVar1 = FUN_0100ca98(param_2, param_1 + 0xca, param_1 + 0xcb);
        if (iVar1 == 0) {
            FUN_01008d00(0x2d, 0xfc2);
        }
        param_1[0xca] = param_1[0xca] | 2;
    }
    FUN_0100ef88(param_1 + 0xc0, ((uintptr_t)&rodata_101113d) /*=0x101113d*/, 2);
}

