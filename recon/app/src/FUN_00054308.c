/* Reconstructed FUN_00054308 @ 0x54308  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00054250(int);
extern void FUN_000566a4(int);
extern int FUN_00056908(unsigned,int);
extern void FUN_00056a68(int,int);
extern void FUN_00056da8(int,int,int);
extern void FUN_0005e47c(void);
extern int FUN_00080e38(int);
extern void FUN_00080ea2(int,int,void*);

void FUN_00054308(int param_1){
    char *pcVar6 = *(char**)(param_1+0xc);
    unsigned uVar1 = *(unsigned short*)(pcVar6+1);
    char cVar5 = *pcVar6;
    int uVar3;
    volatile int loc[8];
    int iVar2 = FUN_00056908(uVar1, 0xf);
    if (iVar2 == 0){
        loc[0]=3; loc[1]=0; loc[2]=uVar1; loc[3]=0x000f2e3c;
        FUN_00080ea2(0x00088138, 0x1840, (void*)&loc[0]);
        return;
    }
    if (cVar5 == 0){
        cVar5 = pcVar6[3];
        *(char*)(iVar2+0xb) = cVar5;
        if (*(char*)(iVar2+2) == 1){
            if (cVar5 != 0) FUN_0005e47c();
            int iVar4 = FUN_00080e38(iVar2);
            if (iVar4 == 0){
                uVar3 = FUN_00054250(5);
                FUN_00056da8(iVar2, 5, uVar3);
                loc[4]=2; loc[5]=0x000f30dd;
                FUN_00080ea2(0x00088138, 0x1040, (void*)&loc[4]);
                FUN_00056a68(iVar2, 5);
                goto LAB;
            }
        }
        uVar3 = FUN_00054250(0);
        cVar5 = 0;
    } else {
        uVar3 = FUN_00054250(cVar5);
    }
    FUN_00056da8(iVar2, cVar5, uVar3);
    LAB:
    FUN_000566a4(iVar2);
}

