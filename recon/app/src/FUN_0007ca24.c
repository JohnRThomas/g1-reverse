/* Reconstructed FUN_0007ca24 @ 0x7ca24  (parity: 300/300 trials, PROVEN) */

extern int FUN_00025788(int,int,int,int,int);
void FUN_0007ca24(int param_1, unsigned char *param_2)
{
    unsigned char stackbuf[4];
    *param_2 = 0;
    int iVar1 = FUN_00025788(param_1, 0x2004, (int)&stackbuf[3], 1, param_1);
    if (iVar1 == 0) {
        if (stackbuf[3] != 0) {
            *param_2 = 1;
        } else {
            *param_2 = 0;
        }
    }
}

