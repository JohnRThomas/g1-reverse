/* Reconstructed FUN_00080ca0 @ 0x80ca0  (parity: 300/300 trials, PROVEN) */

extern void FUN_00086c78(void *a, int b, int c);
extern int FUN_00081326(int a, void *b);
extern int FUN_00086be4(int a, void *b, int c);

int FUN_00080ca0(int param_1, int param_2)
{
    unsigned char decoded[16];
    unsigned char key[3];
    int iVar2;

    decoded[0] = *(volatile unsigned char *)(param_2 + 3);
    decoded[1] = *(volatile unsigned char *)(param_2 + 4);
    decoded[2] = *(volatile unsigned char *)(param_2 + 5);
    FUN_00086c78(decoded + 3, 0, 13);
    iVar2 = FUN_00081326(param_1, decoded);
    if (iVar2 == 0) {
        key[0] = decoded[0];
        key[1] = decoded[1];
        key[2] = decoded[2];
        iVar2 = FUN_00086be4(param_2, key, 3);
        return iVar2 == 0;
    }
    return 0;
}
