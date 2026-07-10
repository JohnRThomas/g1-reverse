/* Reconstructed FUN_0005a090 @ 0x5a090  (parity: 300/300 trials, PROVEN) */

extern int FUN_00080f92(unsigned char a, int b);
extern int FUN_00059bcc(unsigned char a, int b);
extern void FUN_00082928(void);
extern int FUN_0005a044(void);
extern void FUN_00082a42(int a, int b, void *c);

void FUN_0005a090(int param_1)
{
    int iVar1;

    iVar1 = FUN_00080f92(*(unsigned char *)(param_1 + 8), param_1 + 0x90);
    if (iVar1 == 0) {
        iVar1 = FUN_00059bcc(*(unsigned char *)(param_1 + 8), param_1 + 0x90);
        if (iVar1 != 0) {
            FUN_00082928();
        }
    } else {
        int iStack_18 = FUN_0005a044();
        if (iStack_18 != 0) {
            int local_20 = 3;
            int local_1c = 0xf47c1;
            (void)local_1c;
            FUN_00082a42(0x88128, 0x1840, &local_20);
        }
    }
}

