/* Reconstructed FUN_00085898 @ 0x85898  (parity: 300/300 trials, PROVEN) */

extern void FUN_0008705a(void*, int, int);
extern unsigned int FUN_00070f1c(int, unsigned int, int, void*, int, int);

unsigned int FUN_00085898(int param_1, unsigned int param_2)
{
    unsigned int uVar2 = *(volatile unsigned int*)(param_1 + 0x24);
    unsigned char buf[32];
    volatile unsigned int local_18;
    volatile unsigned int local_14;
    local_18 = uVar2;
    local_14 = param_2;
    FUN_0008705a(buf, param_1, 0x20);
    unsigned int uVar1 = FUN_00070f1c(param_1, uVar2, 0x35, buf, 0x28, 1);
    return uVar1 & ((int)uVar1 >> 31);
}

