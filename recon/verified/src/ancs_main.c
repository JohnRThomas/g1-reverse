/* Reconstructed ancs_main @ 0x19950  (parity: 300/300 trials, PROVEN) */
extern int DEBUG_PRINT(int a, ...);
extern int FUN_000167a8(int a, ...);
extern int FUN_00019c70(int a, ...);
extern int FUN_0007c0a8(int a, ...);
extern int FUN_00054a44(int a, ...);
extern int FUN_00054b70(int a, ...);
extern int FUN_0005e6d4(int a, ...);
extern int FUN_0007f192(int a, ...);
extern int FUN_0001905c(int a, ...);
extern int FUN_000191d8(int a, ...);
extern int FUN_000572fc(int a, ...);
extern int FUN_00057330(int a, ...);
extern int FUN_0005a9d8(int a, ...);
extern int FUN_000181f0(int a, ...);
extern int FUN_00019308(int a, ...);
extern int FUN_000198cc(int a, ...);
extern int FUN_0004c0a8(int a, ...);

unsigned int ancs_main(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int *piVar1;
    int iVar2;
    unsigned int uVar3;
    int iVar4;
    int iVar5;

    piVar1 = (int*)0x2000230cUL;
    *(volatile unsigned int*)0x20006ab8UL = (unsigned int)param_1;
    if (0 < *piVar1) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0,0,param_3,0,param_4);
        } else {
            FUN_00019c70(0);
        }
    }
    uVar3 = 0;
    iVar5 = 0x32;
    iVar4 = 5;
    do {
        for (;;) {
            iVar2 = FUN_000167a8(0);
            if (*(volatile char*)(iVar2 + 0x1058) != 0) break;
            if (iVar5 == 0) break;
            FUN_0007c0a8(100);
            iVar5 = iVar5 - 1;
        }
        iVar2 = FUN_00054a44(0);
        if (iVar2 == 0) break;
        FUN_00054b70(0);
        DEBUG_PRINT(uVar3, iVar2, iVar4);
        iVar4 = iVar4 - 1;
        FUN_0007c0a8(1000);
    } while (iVar4 != 0);
    FUN_0005e6d4(0, 0);
    FUN_0007f192(0);
    iVar4 = FUN_0001905c(param_1 + 0x34);
    uVar3 = 0;
    if (iVar4 == 0) goto LAB_00019a16;
    do {
        DEBUG_PRINT(uVar3, iVar4);
        for (;;) {
            DEBUG_PRINT(0,0);
            FUN_0007c0a8(1000);
            if (0 < *piVar1) {
                if (*(volatile unsigned int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0,0);
                } else {
                    FUN_00019c70(0);
                }
            }
            FUN_0007c0a8(500);
            FUN_0004c0a8(1);
LAB_00019a16:
            iVar4 = FUN_000191d8(0);
            uVar3 = 0;
            if (iVar4 != 0) break;
            iVar4 = FUN_000572fc(0);
            uVar3 = 0;
            if (iVar4 != 0) goto LAB_00019a2c;
            iVar4 = FUN_00057330(0);
            uVar3 = 0;
            if (iVar4 != 0) goto LAB_00019a2c;
            FUN_0005a9d8(0);
            iVar4 = FUN_000181f0(0);
            uVar3 = 0;
            if (iVar4 != 0) goto LAB_00019a2c;
            iVar4 = FUN_00019308(0);
            if (iVar4 == 0) {
                FUN_000198cc(param_1);
                return 0;
            }
            DEBUG_PRINT(0,0,iVar4);
            continue;
LAB_00019a2c:
            DEBUG_PRINT(uVar3);
        }
    } while (1);
    return iVar4;
}

