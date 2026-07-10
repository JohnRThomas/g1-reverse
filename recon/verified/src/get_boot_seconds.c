/* Reconstructed get_boot_seconds @ 0x4a51c  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0007d9a4(void);
extern int FUN_0000e1a4(void);
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);

int get_boot_seconds(void)
{
    unsigned long long uVar3 = FUN_0007d9a4();
    (void)uVar3;
    int iVar1 = FUN_0000e1a4();
    int iVar2 = *(volatile int*)0x2000a0b0UL;
    int diff = iVar1 - iVar2;
    if (*(volatile int*)0x2000230cUL > 2) {
        if (*(volatile unsigned int*)0x20007554UL == 0) {
            DEBUG_PRINT();
        } else {
            FUN_00019c70();
        }
    }
    return diff;
}

