#include "g1_net_symbols.h"
/* net-core FUN_0103494c @ 0x103494c  (parity 300 trials PROVEN) */

extern int FUN_010344d4(void);
extern unsigned long long FUN_010344a8(unsigned int a);
extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

unsigned int FUN_0103494c(unsigned int param_1, int param_2)
{
    int iVar1;
    unsigned int uVar2;
    unsigned long long uVar3;
    unsigned int base;
    unsigned char *ptr;
    unsigned short hw;
    if (param_2 == 0) {
        FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, ((uintptr_t)&rodata_103e66f) /*=0x103e66f*/, 0x265);
        FUN_01039bb0(((uintptr_t)&rodata_103e66f) /*=0x103e66f*/, 0x265);
        return 0;
    }
    iVar1 = FUN_010344d4();
    uVar2 = 0x0bad0004;
    if (iVar1 != 0) {
        uVar3 = FUN_010344a8(param_1);
        uVar2 = 0x0bad0000;
        base = ((uintptr_t)&g_sdc_res_pool_slot_tbl) /*=0x210006a8*/;
        ptr = (unsigned char *)(unsigned int)(uVar3 >> 32);
        hw = *(unsigned short *)(base + ((unsigned int)uVar3 + 8) * 2);
        *ptr = (unsigned char)(hw >> 0xd);
    }
    return uVar2;
}

