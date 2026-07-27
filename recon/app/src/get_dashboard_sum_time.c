/* Reconstructed get_dashboard_sum_time @ 0x4a960  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0007daa4(void);
extern unsigned int FUN_000167a8(void);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

long long get_dashboard_sum_time(void)
{
    unsigned long long uVar7;
    unsigned int iVar1;
    unsigned long long field;
    long long lVar8;

    uVar7 = FUN_0007daa4();
    iVar1 = FUN_000167a8();
    field = *(volatile unsigned long long*)(iVar1 + 0x1094);
    if ((long long)field >= (long long)uVar7) {
        iVar1 = FUN_000167a8();
        field = *(volatile unsigned long long*)(iVar1 + 0x1094);
        uVar7 = FUN_0007daa4();
        lVar8 = (long long)(field - uVar7);
    } else {
        uVar7 = FUN_0007daa4();
        iVar1 = FUN_000167a8();
        field = *(volatile unsigned long long*)(iVar1 + 0x1094);
        lVar8 = (long long)(uVar7 - field);
    }
    if (1 < *(volatile int*)0x2000230cUL) {
        unsigned int loP = (unsigned int)lVar8;
        unsigned int hiP = (unsigned int)((unsigned long long)lVar8 >> 32);
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT(0xf0369, 0xf0492, loP, hiP);
        } else {
            FUN_00019c70(0xf0369, 0xf0492, loP, hiP);
        }
    }
    return lVar8;
}

