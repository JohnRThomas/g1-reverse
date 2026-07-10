/* Reconstructed FUN_000235a4 @ 0x235a4  (parity: 300/300 trials, PROVEN) */

extern int FUN_00072240(unsigned int, void*, int, int);
extern void FUN_00086c04(unsigned int, void*, int);
extern void DEBUG_PRINT(unsigned int);

int FUN_000235a4(unsigned int param_1)
{
    unsigned char buf[208];
    int iVar1 = FUN_00072240(0x200079a0U, buf, 0, 0);
    if (iVar1 == 0) {
        FUN_00086c04(param_1, buf, 0xc9);
    } else {
        DEBUG_PRINT(0x9e85dU);
    }
    return iVar1;
}

