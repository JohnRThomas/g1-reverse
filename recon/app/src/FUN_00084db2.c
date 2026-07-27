/* Reconstructed FUN_00084db2 @ 0x84db2  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007ef80(int a, int b, char *c, int d, int e);
extern unsigned int FUN_00084d8c(unsigned int, unsigned char *, int);

unsigned int FUN_00084db2(int param_1, char *param_2, int param_3, int param_4)
{
    int iVar1;
    unsigned int uVar2;
    char cVar3;

    iVar1 = FUN_0007ef80(param_1, param_3, param_2, 1, param_4);
    if (iVar1 < 0) {
        uVar2 = 1;
    } else {
        iVar1 = FUN_00084d8c(param_1, param_2, 1);
        if (iVar1 == 0) {
            if (*param_2 == 1) {
                cVar3 = 1;
            } else {
                cVar3 = 2;
            }
        } else {
            cVar3 = 3;
        }
        uVar2 = 0;
        *param_2 = cVar3;
    }
    return uVar2;
}

