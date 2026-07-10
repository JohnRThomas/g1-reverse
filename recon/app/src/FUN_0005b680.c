/* Reconstructed FUN_0005b680 @ 0x5b680  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005833c(int,...);
extern int FUN_0005858c(int,...);
extern int FUN_00058eb0(int,...);
extern int FUN_0005b0dc(int,...);
extern int FUN_0005f200(int,...);
extern int FUN_0005f24c(int,...);
extern int FUN_0005f5d0(int,...);
extern int FUN_0007e2ec(int,...) __attribute__((noreturn));
extern int FUN_0007e2fa(int,...);
extern int FUN_00082114(int,...);
extern int FUN_000825ac(int,...);
extern int FUN_00082a42(int,...);
extern int FUN_00082cba(int,...);
extern int FUN_00086c04(int,...);

unsigned FUN_0005b680(int param_1, unsigned short param_2, int param_3)
{
    int iVar1,iVar2; unsigned uVar3; unsigned short *puVar4; int *piVar5,*piVar6;
    unsigned local_28,local_24;
    iVar2 = FUN_00082cba(param_1, *(unsigned*)(param_3+4), 0x94);
    if(iVar2 == 0){
        iVar2 = FUN_0005b0dc(param_1, *(unsigned*)(param_3+4), 1);
        if(iVar2 == 0){
            local_24 = 0x000f4aeb; local_28 = 2;
            FUN_00082a42(0x00088128, 0x1080, &local_28);
            uVar3 = 0xffffffea;
        } else {
            iVar2 = FUN_00058eb0(param_1, 0x1b, *(unsigned short*)(param_3+0xc) + 2);
            if(iVar2 != 0){
                puVar4 = (unsigned short*)FUN_0005f5d0(iVar2+0xc, 2);
                *puVar4 = param_2;
                FUN_0005f5d0(iVar2+0xc, *(unsigned short*)(param_3+0xc));
                FUN_00086c04((int)(puVar4+1), *(unsigned*)(param_3+8), *(unsigned short*)(param_3+0xc));
                FUN_000825ac(iVar2, *(unsigned*)(param_3+0x10), *(unsigned*)(param_3+0x14), 1);
                if(param_1 == 0){
                    FUN_0007e2fa(0x00099cbd, 0x000f4b3d, 0x000f46b8, 0xf22);
                    uVar3 = 0xf22;
                } else {
                    if(iVar2 != 0){
                        iVar1 = FUN_0005858c(0);
                        if(iVar1 == 0){
                            FUN_0005833c(*(unsigned*)(iVar2+0x18));
                            FUN_0005f24c(iVar2);
                            uVar3 = 0xffffff80;
                        } else {
                            FUN_0005f200(iVar1+0xc, iVar2);
                            piVar5 = *(int**)(iVar1+0x30);
                            if(piVar5 != 0){
                                piVar6 = (int*)*piVar5;
                                piVar5 = piVar5 - 100;
                                if(piVar6 != 0){ piVar6 = piVar6 - 100; }
                                while(iVar2 = FUN_00082114((int)piVar5, iVar1+0xc), piVar5 = piVar6, iVar2 != 0){
                                    while(1){
                                        if(piVar5 == 0) goto LAB_00059a5a;
                                        piVar6 = (int*)piVar5[100];
                                        if(piVar6 != 0){ piVar6 = piVar6 - 100; }
                                        if(iVar2 != -2) break;
                                        iVar2 = -2;
                                        piVar5 = piVar6;
                                    }
                                }
                            }
LAB_00059a5a:
                            uVar3 = 0;
                        }
                        return uVar3;
                    }
                    FUN_0007e2fa(0x00099cbd, 0x000f4b44, 0x000f46b8, 0xf23);
                    uVar3 = 0xf23;
                }
                FUN_0007e2ec(0x000f46b8, uVar3);
            }
            local_24 = 0x000f4bde; local_28 = 2;
            FUN_00082a42(0x00088128, 0x1080, &local_28);
            uVar3 = 0xfffffff4;
        }
    } else {
        local_24 = 0x000f4ad5; local_28 = 2;
        FUN_00082a42(0x00088128, 0x1080, &local_28);
        uVar3 = 0xffffffff;
    }
    return uVar3;
}

