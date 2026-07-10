/* Reconstructed FUN_000338ec @ 0x338ec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int FUN_00019b54(int,...);
extern int FUN_00019c70(void);
extern int FUN_00019da4(int,...);
extern int FUN_00034980(int,...);
extern int FUN_00076d6c(int,...);
extern int FUN_00076d7c(int,...);
extern int FUN_00086c04(int,...);
extern int FUN_00086c78(int,...);

void FUN_000338ec(int param_1, unsigned char *param_2, int param_3)
{
    int *piVar1; unsigned uVar2; int iVar3; unsigned char *puVar4; unsigned uVar5;
    unsigned local_b4; unsigned char auStack_b0[16]; unsigned char auStack_a0[132];

    if(param_1==0 || param_2==0 || param_3==0){
        if(1 < *(volatile int*)0x2000230c){
            if(*(volatile int*)0x20007554 != 0){ FUN_00019c70(); return; }
            DEBUG_PRINT(0x000a7c2d, 0x000a82e2); return;
        }
    } else {
        puVar4 = *(unsigned char**)(param_1+0x10);
        local_b4 = 0;
        FUN_00086c78((int)auStack_b0, 0, 0x10);
        *(unsigned char*)&local_b4 = *param_2;
        *puVar4 = *param_2;
        puVar4[1] = param_2[1];
        *(unsigned*)(param_1+0x14) = *(unsigned short*)(puVar4+2) + 4;
        piVar1 = (int*)0x20007da8;
        uVar5 = (unsigned)(unsigned char)puVar4[1];
        if(uVar5==2 || uVar5==4){
            *(unsigned short*)(puVar4+2) = 0x1b4;
            FUN_00086c04((int)(puVar4+4), param_3);
            if(2 < *(volatile int*)0x2000230c){
                if(*(volatile int*)0x20007554 == 0){
                    DEBUG_PRINT(0x000a7c4a, 0x000a82e2, uVar5);
                } else { FUN_00019c70(); }
            }
            FUN_00019b54(param_1, (int)auStack_a0, 8);
        } else {
            if(*(volatile int*)0x20007da8 == 0){
                iVar3 = FUN_00076d6c(0x800);
                *piVar1 = iVar3;
                if(iVar3==0){
                    if(*(volatile int*)0x20007554 == 0){
                        DEBUG_PRINT(0x000a7c9c, 0x000a82c4, 0x19f);
                    } else { FUN_00019c70(); }
                } else {
                    FUN_00086c78(iVar3, 0, 0x800);
                }
            }
            if(*piVar1 != 0){
                iVar3 = FUN_00019da4(*piVar1, param_3, puVar4[2]);
                uVar2 = local_b4;
                *((unsigned char*)&local_b4 + 1) = (unsigned char)iVar3;
                *((unsigned char*)&local_b4 + 3) = (unsigned char)(uVar2 >> 24);
                *((unsigned char*)&local_b4 + 2) = *(unsigned char*)(param_3+1);
                if(iVar3 == 0xc9){
                    FUN_00034980(*piVar1, (int)(puVar4+4));
                    if(2 < *(volatile int*)0x2000230c){
                        if(*(volatile int*)0x20007554 == 0){
                            DEBUG_PRINT(0x000a7cb6, 0x000a82e2);
                        } else { FUN_00019c70(); }
                    }
                    *(unsigned short*)(puVar4+2) = 0x1b4;
                    FUN_00019b54(param_1, (int)auStack_a0, 8);
                    *((unsigned char*)&local_b4 + 1) = 0xc9;
                    FUN_00076d7c(*piVar1);
                    *piVar1 = 0;
                }
            }
            (*(void(**)(int,...))(param_1+0xc))((int)&local_b4, 0x14);
        }
    }
    return;
}

