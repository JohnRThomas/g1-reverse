/* Reconstructed FUN_000741a4 @ 0x741a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(void*);
extern int FUN_0007205c(void*);
extern void FUN_00072078(void*);
extern void FUN_000737d8(int);
extern void FUN_00073cdc(void*,void*);
extern void FUN_00074d74(void*);
extern void FUN_0007e2ec(unsigned,unsigned);
extern void FUN_0007e2fa(unsigned,...);
extern void FUN_0008664c(void);

void FUN_000741a4(uint8_t *param_1){
    unsigned uVar6=0;
    FUN_00074d74(param_1+0x18);
    int iVar4 = FUN_00072040((void*)0x2000b490);
    if (iVar4==0){
        FUN_0007e2fa(0x00099cbd,0x000f0920,0x000f08c7,0x72);
        FUN_0007e2fa(0x000f0935,0x2000b490);
        uVar6=0x72;
        FUN_0007e2ec(0x000f08c7,uVar6);
        return;
    }
    FUN_00072078((void*)0x2000b490);
    if ((int8_t)param_1[0xd] < 0){
        param_1[0xd] = param_1[0xd] & 0x7f;
        FUN_00073cdc((void*)0x2000b464, param_1);
    }
    int iVar5 = *(int*)(0x2000b448+8);
    param_1[0xd] = param_1[0xd] | 0x10;
    FUN_000737d8(iVar5 == (int)(intptr_t)param_1);
    iVar5 = FUN_0007205c((void*)0x2000b490);
    if (iVar5 != 0){
        if (*(int*)(0x2000b448+8) != (int)(intptr_t)param_1) return;
        FUN_0008664c();
        return;
    }
    FUN_0007e2fa(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
    FUN_0007e2fa(0x000f090b,0x2000b490);
    uVar6=0xf0;
    FUN_0007e2ec(0x000f08c7,uVar6);
}
