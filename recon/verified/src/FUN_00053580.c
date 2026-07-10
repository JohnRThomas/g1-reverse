/* Reconstructed FUN_00053580 @ 0x53580  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00052c98(unsigned int a, unsigned int b);
extern void FUN_00080ea2(unsigned int a, unsigned int b, void *c);

void FUN_00053580(unsigned int param_1, int param_2)
{
    unsigned short uVar1;
    unsigned int local_28;
    unsigned int local_24;
    unsigned int uStack_20;
    unsigned int local_1c;
    unsigned int uStack_18;
    unsigned short local_14;

    uVar1 = *(unsigned short *)(param_2 + 0x10);
    uStack_18 = FUN_00052c98(*(unsigned int *)(param_2 + 0xc), (unsigned int)uVar1);
    local_24 = 0x000f2df8UL;
    local_14 = 0x402;
    local_28 = 0x01000005UL;
    uStack_20 = param_1;
    local_1c = (unsigned int)uVar1;
    FUN_00080ea2(0x00088138UL, 0x2c80, &local_28);
}

