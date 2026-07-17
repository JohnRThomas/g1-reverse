/* Reconstructed get_boot_seconds @ 0x4a51c  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0007d9a4(void);
extern int FUN_0000e1a4(unsigned int,unsigned int,unsigned int,unsigned int);
extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int);
extern void FUN_00019c70(unsigned int,unsigned int,unsigned int,unsigned int);

int get_boot_seconds(void)
{
    unsigned long long uVar3 = FUN_0007d9a4();
    int iVar1 = FUN_0000e1a4((unsigned int)uVar3,
                             (unsigned int)(uVar3 >> 32),1000,0);
    int iVar2 = *(volatile int*)0x2000a0b0UL;
    int diff = iVar1 - iVar2;
    if (*(volatile int*)0x2000230cUL > 2) {
        unsigned int sink = *(volatile unsigned int*)0x20007554UL;
        if (sink == 0) {
            DEBUG_PRINT(0x000f02adUL,0x000f02ffUL,(unsigned int)diff,sink);
        } else {
            FUN_00019c70(0x000f02adUL,0x000f02ffUL,(unsigned int)diff,sink);
        }
    }
    return diff;
}
