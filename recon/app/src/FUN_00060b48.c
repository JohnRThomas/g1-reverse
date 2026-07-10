/* Reconstructed FUN_00060b48 @ 0x60b48  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern int FUN_00060a10(int);
extern void FUN_00060a5c(int);
extern int FUN_00060ab0(int,void*,int,int,int);
extern int FUN_00066994(int,int,int);
extern int FUN_00066ae0(void);
extern void FUN_00066b24(void);
extern int FUN_0007ef2e(void);
extern int FUN_000838dc(int,int);
extern int FUN_0008397e(int);
extern void FUN_00086384(int);

uint FUN_00060b48(int param_1, int param_2, unsigned param_3, unsigned param_4){
    int iVar5 = *(int*)(param_1+0x10);
    int iVar4 = *(int*)(param_1+4);
    int iVar3 = param_1;
    volatile int local[3];
    int iVar1 = FUN_0007ef2e();
    if (iVar1 == 0){
        uint uVar2;
        if (param_2 != 0){
            if (param_2 != 1) return 0xffffff7a;
            uVar2 = FUN_000838dc(*(int*)(iVar4+0x34), 0);
            if ((int)uVar2 < 0) return uVar2;
            iVar3 = FUN_00066994(iVar4, 0x000838cb, iVar5);
            if (iVar3 != 0x0bad0000) return 0xfffffffb;
            uVar2 = FUN_0008397e(param_1);
            if ((int)uVar2 < 0) return uVar2;
            FUN_00060a5c(param_1);
            return 0;
        }
        uVar2 = FUN_00060a10(param_1);
        if ((int)uVar2 < 0) return uVar2;
        uVar2 = *(uint8_t*)(iVar5+0x60);
        if (uVar2==0){
            iVar1 = FUN_00066ae0();
            if (iVar1 == 0x0bad0000){
                local[0]=0xb9; local[1]=uVar2; local[2]=uVar2;
                uVar2 = FUN_00060ab0(param_1, (void*)local, 0, 0xb9, iVar3);
                if ((int)uVar2 < 0) return uVar2;
                FUN_00086384(10);
                FUN_00066b24();
                uVar2 = FUN_000838dc(*(int*)(iVar4+0x34), 1);
                return uVar2 & ((int)uVar2 >> 0x1f);
            }
        }
    }
    return 0xfffffff0;
}

