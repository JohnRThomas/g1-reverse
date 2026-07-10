/* Reconstructed FUN_0007f210 @ 0x7f210  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007e9dc(int a, int b, int c, int d);
int FUN_0007f210(unsigned int *param_1, int param_2, int param_3) {
    unsigned short h = *(unsigned short*)((char*)param_1 + 4);
    int iVar1 = FUN_0007e9dc((int)param_1[0], (int)h, param_2, param_3);
    if (param_3 <= iVar1) iVar1 = param_3;
    return iVar1;
}

