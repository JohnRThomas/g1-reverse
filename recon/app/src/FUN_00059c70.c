/* Reconstructed FUN_00059c70 @ 0x59c70  (parity: 300/300 trials, PROVEN) */

extern int FUN_000814e6(int a, unsigned char b);
extern int FUN_000826b2(void *a, unsigned int b);

unsigned char * FUN_00059c70(int param_1)
{
    unsigned int uVar1;
    int iVar2;
    unsigned char *puVar3;
    int iVar4;

    uVar1 = 0x000f2b3aUL;
    iVar4 = 0;
    puVar3 = (unsigned char *)0x2000af18UL;
    while (1) {
        if (param_1 == 0) {
            iVar2 = FUN_000826b2(puVar3 + 1, uVar1);
        } else {
            iVar2 = FUN_000814e6(param_1, *puVar3);
        }
        if (iVar2 != 0) break;
        iVar4 = iVar4 + 1;
        puVar3 = puVar3 + 0x10;
        if (iVar4 == 3) {
            return (unsigned char *)0;
        }
    }
    return puVar3;
}

