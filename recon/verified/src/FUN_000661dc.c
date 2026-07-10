/* Reconstructed FUN_000661dc @ 0x661dc  (parity: 300/300 trials, PROVEN) */

extern void FUN_000500c8(unsigned int);
extern void FUN_00066130(unsigned int);

void FUN_000661dc(void)
{
    FUN_000500c8(0x26);
    *(volatile unsigned int*)(0x50026000UL + 0x500) = 0;
    if (*(volatile unsigned char*)(0x2000b330UL + 0x15) == 0) {
        unsigned int uVar3 = *(volatile unsigned int*)(0x50026000UL + 0x544);
        FUN_00066130(*(volatile unsigned int*)(0x50026000UL + 0x540));
        FUN_00066130(uVar3);
    }
    *(volatile unsigned char*)(0x2000b330UL + 0x10) = 0;
    return;
}

