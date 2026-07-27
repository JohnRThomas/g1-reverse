/* Reconstructed FUN_00016110 @ 0x16110  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_00083dba(int,int,int,int);
extern int FUN_00083dc8(int, ...);

int FUN_00016110(int param_1, unsigned int param_2, int param_3)
{
    int iVar1;
    unsigned int uStack_14;
    unsigned int uStack_10;

    iVar1 = *(volatile int *)(0x00087ce0 + 4);
    uStack_14 = param_2;
    uStack_10 = param_3;
    *((unsigned char *)&uStack_14 + 3) = 0;
    (void)uStack_10;
    FUN_00083dc8(*(int *)(iVar1 + 0x1c), 3, 0x10, 0xeb, param_1);
    FUN_00083dc8(*(int *)(iVar1 + 0x1c), 3, 0x11, 1);
    FUN_00083dc8(*(int *)(iVar1 + 0x1c), 3, 0x12, 0xad);
    FUN_00083dc8(*(int *)(iVar1 + 0x1c), 3, 0x13, 1);
    FUN_00083dc8(*(int *)(iVar1 + 0x1c), 3, 0x14, 0x3f);
    FUN_00083dc8(*(int *)(iVar1 + 0x1c), 3, 0x15, 3);
    FUN_00083dc8(*(int *)(iVar1 + 0x1c), 3, 0x16, 0x2e);
    FUN_00083dc8(*(int *)(iVar1 + 0x1c), 3, 0x17, 2);
    FUN_00083dba(*(int *)(iVar1 + 0x1c), 3, 0x10, (int)&uStack_14 + 3);
    DEBUG_PRINT(0x0009951c, uStack_14 >> 0x18);
    FUN_00083dba(*(int *)(iVar1 + 0x1c), 3, 0x11, (int)&uStack_14 + 3);
    DEBUG_PRINT(0x00099528, uStack_14 >> 0x18);
    FUN_00083dba(*(int *)(iVar1 + 0x1c), 3, 0x12, (int)&uStack_14 + 3);
    DEBUG_PRINT(0x00099534, uStack_14 >> 0x18);
    FUN_00083dba(*(int *)(iVar1 + 0x1c), 3, 0x13, (int)&uStack_14 + 3);
    DEBUG_PRINT(0x00099540, uStack_14 >> 0x18);
    FUN_00083dba(*(int *)(iVar1 + 0x1c), 3, 0x14, (int)&uStack_14 + 3);
    DEBUG_PRINT(0x0009954c, uStack_14 >> 0x18);
    FUN_00083dba(*(int *)(iVar1 + 0x1c), 3, 0x15, (int)&uStack_14 + 3);
    DEBUG_PRINT(0x00099558, uStack_14 >> 0x18);
    FUN_00083dba(*(int *)(iVar1 + 0x1c), 3, 0x16, (int)&uStack_14 + 3);
    DEBUG_PRINT(0x00099564, uStack_14 >> 0x18);
    FUN_00083dba(*(int *)(iVar1 + 0x1c), 3, 0x17, (int)&uStack_14 + 3);
    DEBUG_PRINT(0x00099570, uStack_14 >> 0x18);
    return 0;
}
