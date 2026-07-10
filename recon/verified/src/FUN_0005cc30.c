/* Reconstructed FUN_0005cc30 @ 0x5cc30  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void *a, int b, unsigned int c, unsigned int d, unsigned int e);
extern int FUN_00055cb4(unsigned int a, unsigned int b);
extern void FUN_00083090(void *a, unsigned int b);
extern unsigned int FUN_00055e58(void);

unsigned int FUN_0005cc30(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar2;
    FUN_00086c78((void*)param_1, 0, 0xf0, param_4, param_4);
    int iVar1 = FUN_00055cb4(param_1+0x27, 0x10);
    if (iVar1 == 0) {
        FUN_00083090((void*)param_1, 5);
        uVar2 = FUN_00055e58();
        *(volatile unsigned int*)0x2000af48UL = uVar2;
        uVar2 = 0;
    } else {
        uVar2 = 8;
    }
    return uVar2;
}

