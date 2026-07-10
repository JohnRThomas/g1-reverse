/* Reconstructed FUN_00085076 @ 0x85076  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00012c18(void);
extern int FUN_0006466c(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_00064b1c(unsigned int a);

unsigned int FUN_00085076(unsigned int param_1, unsigned int param_2)
{
    unsigned int uVar1;
    int iVar2;
    uVar1 = FUN_00012c18();
    iVar2 = FUN_0006466c(param_1, param_2, uVar1, 0);
    if (iVar2 == 0) {
        FUN_00064b1c(uVar1);
        uVar1 = 0;
    }
    return uVar1;
}

