/* Reconstructed FUN_0004a4b4 @ 0x4a4b4  (parity: 300/300 trials, PROVEN) */

extern unsigned long long FUN_0007d9a4(void);

void FUN_0004a4b4(unsigned int param_1, unsigned int param_2)
{
    *(volatile unsigned int*)0x20004df0UL = param_1;
    *(volatile unsigned int*)0x20004df4UL = param_2;
    unsigned long long uVar2 = FUN_0007d9a4();
    *(volatile unsigned int*)0x20004df8UL = (unsigned int)uVar2;
    *(volatile unsigned int*)0x20004dfcUL = (unsigned int)(uVar2 >> 32);
}

