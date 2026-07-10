#include "g1_app_symbols.h"
/* named: FUN_0005fa94 */
/* Reconstructed FUN_0005fa94 @ 0x5fa94  (parity: 300/300 trials, PROVEN) */

extern unsigned long long __aeabi_uldivmod(int a,int b,int c,int d);
extern int k_msgq_get(int a, unsigned b, int c, int d);
extern void FUN_000837a2(unsigned a, unsigned b, void*c);
int FUN_0005fa94(int param_1, unsigned param_2, unsigned param_3, unsigned *param_4, unsigned param_5){
    int iVar3 = *(volatile int*)(param_1 + 0x10);
    unsigned char b = *(volatile unsigned char*)(iVar3 + 0x50);
    unsigned loc[2]; int iVar2;
    if ((int)((unsigned)b << 0x1e) >= 0){
        loc[1] = "Device is not configured" /*=0xf5660*/; iVar2 = -5; loc[0] = 2;
        FUN_000837a2(((uintptr_t)&tbl_880d8) /*=0x881a0*/, 0x1040, loc);
        return iVar2;
    }
    unsigned long long uVar4;
    if (param_5 == 0xffffffffu){
        uVar4 = 0xffffffffffffffffULL;
    } else {
        int r4c = (int)param_5 & ~((int)param_5 >> 31);
        long long lVar1 = (long long)r4c * 0x8000 + 999;
        uVar4 = __aeabi_uldivmod((int)lVar1, (int)((unsigned long long)lVar1 >> 32), 1000, 0);
    }
    iVar2 = k_msgq_get(iVar3 + 0x1c, param_3, (int)(unsigned)uVar4, (int)(unsigned)(uVar4 >> 32));
    if (iVar2 == 0){
        *param_4 = *(volatile unsigned*)(iVar3 + 0x18);
    } else {
        loc[1] = "No audio data to be read" /*=0xf5679*/; loc[0] = 2;
        FUN_000837a2(((uintptr_t)&tbl_880d8) /*=0x881a0*/, 0x1040, loc);
    }
    return iVar2;
}

