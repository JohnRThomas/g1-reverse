/* Reconstructed FUN_0007f594 @ 0x7f594  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007f3f0(void *a, int b, unsigned int c, unsigned int d);
extern void FUN_0007f3c2(void *a);

unsigned int FUN_0007f594(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar2;
    int iVar1 = FUN_0007f3f0((void*)(param_1+0x138), 0xfffffffd, param_3, param_4);
    if ((int)(iVar1 << 0x1e) < 0) {
        FUN_0007f3c2((void*)param_1);
        FUN_0007f3f0((void*)(param_1+0x138), 0xfffffffe, 0, 0);
        uVar2 = 0;
    } else {
        uVar2 = 0xffffff88;
    }
    return uVar2;
}

