/* Reconstructed FUN_00080ca0 @ 0x80ca0  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void *a, int b, int c);
extern int FUN_00081326(int a, void *b);
extern int FUN_00086be4(int a, void *b, int c);

int FUN_00080ca0(int param_1, int param_2)
{
    unsigned char buf[20];
    int iVar2;

    FUN_00086c78(buf, 0, 0xd);
    iVar2 = FUN_00081326(param_1, buf);
    if (iVar2 == 0) {
        iVar2 = FUN_00086be4(param_2, buf, 3);
        return iVar2 == 0;
    }
    return 0;
}

