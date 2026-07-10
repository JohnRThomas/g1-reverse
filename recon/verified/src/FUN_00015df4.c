/* Reconstructed FUN_00015df4 @ 0x15df4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int FUN_000179ec(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_0007c038(int,...);
extern int FUN_00083dc8(int,...);
extern int FUN_00083e0e(int,...);

unsigned FUN_00015df4(unsigned param_1, unsigned param_2)
{
    int *piVar1; int iVar2; unsigned char *puVar3; int iVar4;
    iVar2 = FUN_00083dc8(*(unsigned*)(*(volatile int*)(0x00087cf8+4)+0x1c), 8, 0, 1, param_1, param_2);
    piVar1 = (int*)0x2000230c;
    if(iVar2 < 0){
        if(*(volatile int*)0x2000230c < 1) return 0;
        iVar2 = *(volatile int*)0x20007554;
        puVar3 = (unsigned char*)0x00099329;
        goto LAB_00015e1a;
    }
    if(0 < *(volatile int*)0x2000230c){
        if(*(volatile int*)0x20007554 == 0){ DEBUG_PRINT(0x00099345, 0x00099c3e); }
        else { FUN_00019c70(0); }
    }
    FUN_0007c038(1);
    iVar2 = *(volatile int*)(0x00087d10+4);
    if(*(char*)(*(volatile int*)0x200069fc + 0xed4) == 1){
        iVar4 = FUN_00083dc8(*(unsigned*)(iVar2+0x1c), 4, 10, 1, param_1, param_2);
        if(iVar4 < 0){
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x00099368;
            goto LAB_00015e1a;
        }
        if(0 < *piVar1){
            iVar4 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x0009938c;
LAB_00015e82:
            if(iVar4 == 0){ DEBUG_PRINT((int)puVar3, 0x00099c3e); }
            else { FUN_00019c70(0); }
        }
    } else {
        iVar4 = FUN_00083dc8(*(unsigned*)(iVar2+0x1c), 4, 10, 2, param_1, param_2);
        if(iVar4 < 0){
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x000993a5;
            goto LAB_00015e1a;
        }
        if(0 < *piVar1){
            iVar4 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x000993c9;
            goto LAB_00015e82;
        }
    }
    iVar4 = FUN_00083e0e(*(unsigned*)(iVar2+0x1c), 4, 0xf, 2, 2);
    if(iVar4 < 0){
        if(*piVar1 < 1) return 0;
        iVar2 = *(volatile int*)0x20007554;
        puVar3 = (unsigned char*)0x000993e2;
    } else {
        iVar2 = FUN_00083dc8(*(unsigned*)(iVar2+0x1c), 4, 2, 1);
        if(iVar2 < 0){
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x0009940b;
        } else {
            if(0 < *piVar1){
                if(*(volatile int*)0x20007554 == 0){ DEBUG_PRINT(0x00099427, 0x00099c3e); }
                else { FUN_00019c70(0); }
            }
            FUN_0007c038(1);
            FUN_000179ec(0);
            FUN_0007c038(0xf);
            if(*piVar1 < 1) return 0;
            iVar2 = *(volatile int*)0x20007554;
            puVar3 = (unsigned char*)0x0009943c;
        }
    }
LAB_00015e1a:
    if(iVar2 == 0){ DEBUG_PRINT((int)puVar3, 0x00099c3e); }
    else { FUN_00019c70(0); }
    return 0;
}

