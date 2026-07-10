/* Reconstructed FUN_0007dada @ 0x7dada  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(void);
extern unsigned int FUN_0007dac0(void);

void FUN_0007dada(void)
{
    int iVar1;
    unsigned int uVar2;
    iVar1 = FUN_000167a8();
    if ((*(volatile unsigned char*)(iVar1 + 0x10ac) != 0) && ((uVar2 = FUN_0007dac0()), uVar2 < 7)) {
        iVar1 = FUN_000167a8();
        *(volatile unsigned char*)(iVar1 + 0x10ac) = 0;
    }
}

