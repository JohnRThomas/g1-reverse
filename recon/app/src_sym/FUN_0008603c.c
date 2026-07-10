/* Reconstructed FUN_0008603c @ 0x8603c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00085da2(void *a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern int FUN_00085e1a(void *a, unsigned int b, unsigned int c);

int FUN_0008603c(char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    iVar1 = FUN_00085da2(param_1, 6, param_3, param_4, param_4);
    if ((iVar1 == 0) || ((iVar1 = FUN_00085e1a(param_1, param_2, 4)), iVar1 == 0)) {
        iVar1 = 0;
    } else {
        *(volatile int*)(param_1 + 8) = *(volatile int*)(param_1 + 8) + 1;
    }
    return iVar1;
}

