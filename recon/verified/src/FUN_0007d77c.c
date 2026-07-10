/* Reconstructed FUN_0007d77c @ 0x7d77c  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007d4ec(void);
extern void FUN_00047698(unsigned int a, unsigned int b);
extern void FUN_000476a8(void);

void FUN_0007d77c(unsigned char param_1)
{
    int iVar1;
    unsigned char local_11[5];
    unsigned char local_c[4];

    local_c[0] = 0;
    local_11[0] = param_1;
    iVar1 = FUN_0007d4ec();
    FUN_00047698(0xffffffff, 0xffffffff);
    (*(void (**)(int, void *, int, void *, int))(*(volatile int *)(iVar1 + 0x374) + 8))(
        *(volatile int *)(iVar1 + 0x374), local_11, 1, local_c, 1);
    FUN_000476a8();
}

