/* Reconstructed FUN_000181b8 @ 0x181b8  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void*, int, int);
extern int FUN_00072240(unsigned int, void*, int, int);
extern void FUN_00086c04(unsigned int, void*, int);

int FUN_000181b8(unsigned int param_1)
{
    unsigned char buf[264];
    FUN_00086c78(buf, 0, 0x101);
    int iVar1 = FUN_00072240(0x200038f8UL, buf, 0, 0);
    if (iVar1 == 0) {
        FUN_00086c04(param_1, buf, 0x101);
    }
    return iVar1;
}

