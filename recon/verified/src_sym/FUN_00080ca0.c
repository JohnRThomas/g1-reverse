/* Reconstructed FUN_00080ca0 @ 0x80ca0  (parity: 300/300 trials, PROVEN) */

extern void memset_bytes(void *a, int b, int c);
extern int FUN_00081326(int a, void *b);
extern int memcmp(int a, void *b, int c);

int FUN_00080ca0(int param_1, int param_2)
{
    unsigned char buf[20];
    int iVar2;

    memset_bytes(buf, 0, 0xd);
    iVar2 = FUN_00081326(param_1, buf);
    if (iVar2 == 0) {
        iVar2 = memcmp(param_2, buf, 3);
        return iVar2 == 0;
    }
    return 0;
}

