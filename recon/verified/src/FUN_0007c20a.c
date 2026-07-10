/* Reconstructed FUN_0007c20a @ 0x7c20a  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void *a, unsigned int b, unsigned int c);
extern int FUN_00019c44(void *a);
extern short FUN_0000ef12(void *a);

unsigned int FUN_0007c20a(int param_1)
{
    short sVar1;
    int iVar2;
    unsigned char local_d4;
    unsigned char auStack_d3[203];

    while (1) {
        FUN_00086c78(auStack_d3, 0, 0xca);
        local_d4 = 0xf4;
        iVar2 = FUN_00019c44(auStack_d3);
        if (iVar2 != 0) break;
        sVar1 = FUN_0000ef12(&local_d4);
        (*(void (**)(void *, unsigned short))(param_1 + 0xc))(&local_d4, sVar1 + 1);
    }
    return 0;
}

