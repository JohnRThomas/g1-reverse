/* Reconstructed FUN_0001905c @ 0x1905c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_0007f69e(int,...);
extern int FUN_0007f772(int,...);
extern int FUN_0007f79e(int,...);
#define C8 (*(volatile int*)0x2000230c)
#define CC (*(volatile int*)0x20007554)

int FUN_0001905c(int param_1, unsigned param_2, unsigned param_3, unsigned param_4)
{
    int iVar1; unsigned uVar2;
    iVar1 = FUN_0007f69e(0x20006ae8);
    if(iVar1 == 0){
        iVar1 = FUN_0007f772(0x20006ae8, 0, param_1+0x10, 0x20, param_4);
        if(iVar1 == 0){
            iVar1 = FUN_0007f79e(0x20006ae8, 0, param_1+0x30, 0x20);
            if(iVar1 == 0){
                iVar1 = FUN_0007f772(0x20006ae8, 1, param_1+0x50, 0x20, param_4);
                if(iVar1 == 0){
                    iVar1 = FUN_0007f772(0x20006ae8, 2, param_1+0x70, 0x20, param_4);
                    if(iVar1 == 0){
                        iVar1 = FUN_0007f772(0x20006ae8, 3, param_1+0x90, 0x100);
                        if(iVar1 == 0){
                            iVar1 = FUN_0007f772(0x20006ae8, 5, param_1+400, 0x20);
                            if(iVar1 == 0) return 0;
                            if(C8 < 1) return iVar1;
                            if(CC == 0){ uVar2 = 0x3e4; goto LAB_00019090; }
                            uVar2 = 0x3e4;
                        } else {
                            if(C8 < 1) return iVar1;
                            if(CC == 0){ uVar2 = 0x3dc;
LAB_00019090:
                                DEBUG_PRINT(0x0009ab0c, 0x0009b15e, uVar2, iVar1); return iVar1; }
                            uVar2 = 0x3dc;
                        }
                    } else {
                        if(C8 < 1) return iVar1;
                        if(CC == 0){ uVar2 = 0x3d4; goto LAB_00019090; }
                        uVar2 = 0x3d4;
                    }
                } else {
                    if(C8 < 1) return iVar1;
                    if(CC == 0){ uVar2 = 0x3cc; goto LAB_00019090; }
                    uVar2 = 0x3cc;
                }
            } else {
                if(C8 < 1) return iVar1;
                if(CC == 0){ uVar2 = 0x3c4; goto LAB_00019090; }
                uVar2 = 0x3c4;
            }
        } else {
            if(C8 < 1) return iVar1;
            if(CC == 0){ uVar2 = 0x3bc; goto LAB_00019090; }
            uVar2 = 0x3bc;
        }
    } else {
        if(C8 < 1) return iVar1;
        if(CC == 0){ uVar2 = 0x3b4; goto LAB_00019090; }
        uVar2 = 0x3b4;
    }
    FUN_00019c70(0x0009ab0c, 0x0009b15e, uVar2, iVar1);
    return iVar1;
}

