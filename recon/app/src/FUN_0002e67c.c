/* Reconstructed FUN_0002e67c @ 0x2e67c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void DEBUG_PRINT(int,...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(void);
extern int FUN_0002e594(int a, void *b);
extern int FUN_0008638c(int a);

unsigned FUN_0002e67c(int param_1)
{
    unsigned short local_2c, local_2a;
    unsigned char local_28, local_27, local_26;
    unsigned char *local_24;
    unsigned local_20;
    unsigned char local_1c;
    int iVar5;
    uint uVar6;
    unsigned uVar4;
    volatile int *piVar1 = (volatile int *)0x2000230cUL;
    volatile int *piVar2 = (volatile int *)0x20007b6cUL;
    volatile int *dbg    = (volatile int *)0x20007554UL;
    volatile int *piVar3v= (volatile int *)0x200023fcUL;
    int *piVar3;
    volatile unsigned char *flag8da1 = (volatile unsigned char *)0x20018da1UL;

    local_2c = 0;
    if (param_1 == 0) {
        param_1 = FUN_000167a8();
        param_1 = param_1 + 0xf80;
    }
    *piVar2 = param_1;
    iVar5 = *piVar1;
    if (2 < iVar5) {
        if (*dbg == 0) DEBUG_PRINT(0xa3b3f, 0xa3d00);
        else FUN_00019c70();
    }
    iVar5 = FUN_0002e594(0x7e, &local_2c);
    if (iVar5 == 0) {
        uVar6 = (uint)local_2c;
        if (1 < *piVar1) {
            if (*dbg == 0) DEBUG_PRINT(0xa3b7a, 0xa3d00, uVar6);
            else FUN_00019c70();
        }
        if (uVar6 == 0x5449) {
            iVar5 = FUN_0002e594(0x7f, &local_2c);
            if (iVar5 != 0) {
                if (*piVar1 < 1) return 0xfffffffb;
                iVar5 = *dbg;
                uVar4 = 0xa3bb6;
                goto LAB_0002e6c8;
            }
            uVar6 = (uint)local_2c;
            if (1 < *piVar1) {
                if (*dbg == 0) DEBUG_PRINT(0xa3bd6, 0xa3d00, uVar6);
                else FUN_00019c70();
            }
            if (uVar6 == 0x3001) {
                iVar5 = FUN_0002e594(1, &local_2a);
                piVar3 = (int *)*piVar3v;
                if (iVar5 == 0) {
                    local_27 = (unsigned char)((local_2a & 63999) >> 8) | 6;
                    local_28 = 1;
                    local_26 = (unsigned char)(local_2a & 63999);
                    iVar5 = FUN_0008638c(*piVar3v);
                    if (iVar5 == 0) {
                        if (*piVar1 < 1) return 0xfffffffb;
                        if (*dbg == 0) DEBUG_PRINT(0xa3af8, 0xa3cee);
                        else FUN_00019c70();
                    } else {
                        local_24 = &local_28;
                        local_20 = 3;
                        local_1c = 2;
                        iVar5 = (**(int (***)(int, void *, int, int))(*(int *)(*piVar3 + 8) + 8))(*piVar3, &local_24, 1, 0x45);
                        if (-1 < iVar5) {
                            if (*piVar2 != 0) {
                                *(int *)(*piVar2 + 0x10) = 1;
                            }
                            if (2 < *piVar1) {
                                if (*dbg == 0) DEBUG_PRINT(0xa3c68, 0xa3d00);
                                else FUN_00019c70();
                            }
                            *flag8da1 = 1;
                            return 0;
                        }
                        if (*piVar1 < 1) return 0xfffffffb;
                        if (*dbg == 0) DEBUG_PRINT(0xa3c0c, 0xa3cee);
                        else FUN_00019c70();
                    }
                }
                if (*piVar1 < 1) return 0xfffffffb;
                if (*dbg != 0) {
                    FUN_00019c70();
                    return 0xfffffffb;
                }
                DEBUG_PRINT(0xa3c2d, 0xa3d00);
                return 0xfffffffb;
            }
            if (*piVar1 < 1) return 0xffffff7a;
            iVar5 = *dbg;
            uVar4 = 0xa3bea;
        } else {
            if (*piVar1 < 1) return 0xffffff7a;
            iVar5 = *dbg;
            uVar4 = 0xa3b8e;
        }
        if (iVar5 == 0) DEBUG_PRINT(uVar4, 0xa3d00, uVar6);
        else FUN_00019c70();
        return 0xffffff7a;
    }
    if (*piVar1 < 1) return 0xfffffffb;
    iVar5 = *dbg;
    uVar4 = 0xa3b5a;
LAB_0002e6c8:
    if (iVar5 == 0) DEBUG_PRINT(uVar4, 0xa3d00, (uint)local_2c);
    else FUN_00019c70();
    return 0xfffffffb;
}

