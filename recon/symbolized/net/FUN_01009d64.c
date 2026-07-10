#include "g1_net_symbols.h"
/* net-core FUN_01009d64 @ 0x1009d64  (parity 300 trials PROVEN) */

extern unsigned char FUN_01027470(int, unsigned short);
extern unsigned int FUN_010274ea(int, unsigned char);

unsigned int FUN_01009d64(unsigned short param_1, unsigned char param_2)
{
    int *arr = (int*)((uintptr_t)&g_net_ctx_ptr_table) /*=0x21000b7c*/;
    int iVar4 = arr[param_2];
    unsigned char bVar3 = FUN_01027470(iVar4, param_1);
    unsigned int uVar5;
    if (bVar3 == 0xff) {
        uVar5 = 3;
    } else {
        unsigned short uVar1 = *(unsigned short*)(iVar4 + 6);
        unsigned short uVar2 = *(unsigned short*)(iVar4 + 8);
        uVar5 = FUN_010274ea(iVar4, bVar3);
        unsigned int fnval = ((unsigned int)uVar1 << 16) | uVar2;
        void (*fn)(unsigned short, unsigned int) = (void(*)(unsigned short,unsigned int))fnval;
        fn(param_1, uVar5);
        *(unsigned short*)(iVar4 + 2 + (bVar3 + 4) * 2) = 0xfff0;
        uVar5 = 0;
    }
    return uVar5;
}

