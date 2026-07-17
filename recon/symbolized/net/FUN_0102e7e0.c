#include "g1_net_symbols.h"
/* net-core FUN_0102e7e0 @ 0x102e7e0  (parity 300 trials PROVEN) */

extern int FUN_0102e220(unsigned int);
extern void FUN_0102e4f4(int,unsigned int,int,int,int,unsigned int,void*,void*,unsigned int,int);

void FUN_0102e7e0(int param_1, unsigned short *param_2, int param_3)
{
    unsigned short uVar1 = *param_2;
    int iVar4 = *(int*)(param_2+2);
    unsigned int uVar6 = *(unsigned int*)(param_2+4);
    if (iVar4 != 0) {
        int t = (iVar4 - ((unsigned long)&rodata_103bfec) /*=0x103bfec*/) * 0x2000;
        if ((t >> 16) < 0) {
            iVar4 = 0;
        } else {
            iVar4 = FUN_0102e220((unsigned int)(((unsigned int)(unsigned char)(*param_2)) << 0x1a) >> 0x1d);
        }
    }
    unsigned short *puVar2 = param_2 + 8;
    unsigned int uVar3 = (unsigned int)((*(int*)param_2) << 0xc) >> 0x15;
    unsigned char *pbVar5 = (unsigned char*)((int)puVar2 + uVar3);
    if (uVar3 == 0) {
        puVar2 = 0;
    }
    FUN_0102e4f4(param_1, uVar6, 0, iVar4, 0, (((unsigned int)uVar1) << 0x17) >> 0x1d,
                 puVar2, pbVar5, (((unsigned int)param_2[1]) << 0x10) >> 0x14, param_3);
}
