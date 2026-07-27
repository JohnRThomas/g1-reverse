/* Reconstructed FUN_00083906 @ 0x83906  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007ef3e(unsigned long);
extern void FUN_00072908(int a, int b, unsigned int c, unsigned int d);

void FUN_00083906(char *param_1)
{
    int iVar1;
    iVar1 = *(volatile int*)(param_1 + 0x10);
    FUN_0007ef3e(param_1);
    FUN_00072908(iVar1 + 0x18, 0, 0xffffffff, 0xffffffff);
    if (*(volatile unsigned char*)(iVar1 + 0x60) == 0) {
        *(volatile unsigned int*)0x500055b8UL = 0;
    }
}

