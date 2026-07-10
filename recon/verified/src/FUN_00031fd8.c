/* Reconstructed FUN_00031fd8 @ 0x31fd8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned uint; typedef unsigned char byte;
extern int DEBUG_PRINT(int,...);
extern int FUN_000167a8(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_00022b00(int,...);
extern int FUN_000232f8(int,...);
extern int FUN_0007d14a(int,...);

unsigned FUN_00031fd8(int param_1, unsigned param_2, unsigned *param_3, unsigned char *param_4)
{
    volatile int *piVar1,*piVar2; unsigned uVar3; int iVar4; char cVar5; unsigned char *puVar6;
    unsigned char auStack_9c[8]; char local_94; char local_47; char local_46;
    piVar1 = (volatile int*)0x2000230c;
    if(3 < *piVar1){
        if(*(volatile int*)0x20007554 == 0){ DEBUG_PRINT(0x000a723e, 0x000a76da); }
        else { FUN_00019c70(0); }
    }
    if(param_3 == 0 || param_4 == 0){
        if(0 < *piVar1){
            if(*(volatile int*)0x20007554 == 0){ DEBUG_PRINT(0x000a7266, 0x000a76da); }
            else { FUN_00019c70(0); }
        }
        uVar3 = 0xffffffff;
    } else if(*(volatile char*)0x20019ef3 == 1){
        puVar6 = (unsigned char*)*param_3;
        iVar4 = FUN_000167a8(0);
        *(unsigned char*)(iVar4 + 2) = *(unsigned char*)(param_1 + 4);
        iVar4 = FUN_000167a8(0);
        *(unsigned char*)(iVar4 + 3) = *(unsigned char*)(param_1 + 5);
        iVar4 = FUN_000167a8(0);
        *(unsigned char*)(iVar4 + 4) = *(unsigned char*)(param_1 + 6);
        piVar2 = (volatile int*)0x20007554;
        if(3 < *piVar1){
            if(*(volatile int*)0x20007554 == 0){
                iVar4 = FUN_000167a8(0);
                DEBUG_PRINT(0x000a7293, 0x000a76da, (uint)*(byte*)(iVar4 + 2));
            } else {
                iVar4 = FUN_000167a8(0);
                FUN_00019c70(0x000a7293, 0x000a76da, *(unsigned char*)(iVar4 + 2));
            }
            if(3 < *piVar1){
                if(*piVar2 == 0){
                    iVar4 = FUN_000167a8(0);
                    DEBUG_PRINT(0x000a72ab, 0x000a76da, (uint)*(byte*)(iVar4 + 3));
                } else {
                    iVar4 = FUN_000167a8(0);
                    FUN_00019c70(0x000a72ab, 0x000a76da, *(unsigned char*)(iVar4 + 3));
                }
                if(3 < *piVar1){
                    if(*piVar2 == 0){
                        iVar4 = FUN_000167a8(0);
                        DEBUG_PRINT(0x000a72c6, 0x000a76da, (uint)*(byte*)(iVar4 + 4));
                    } else {
                        iVar4 = FUN_000167a8(0);
                        FUN_00019c70(0x000a72c6, 0x000a76da, *(unsigned char*)(iVar4 + 4));
                    }
                }
            }
        }
        uVar3 = FUN_000167a8(0);
        FUN_00022b00(uVar3, 0);
        cVar5 = 0;
        *puVar6 = 0x1d;
        puVar6[2] = 3;
        puVar6[1] = 1;
        puVar6[3] = 1;
        puVar6[4] = 0;
        do {
            iVar4 = FUN_000232f8((int)auStack_9c);
            if(iVar4 == 0 && *(char*)(param_1 + 4) == local_94 &&
               *(char*)(param_1 + 5) == local_47 && *(char*)(param_1 + 6) == local_46)
                goto LAB_00032102;
            cVar5 = cVar5 + 1;
            FUN_0007d14a(100);
        } while(cVar5 != 5);
        puVar6[4] = 1;
LAB_00032102:
        uVar3 = 0;
        *param_4 = 5;
    } else {
        DEBUG_PRINT(0x000a672f);
        uVar3 = 0xfffffffe;
    }
    return uVar3;
}

