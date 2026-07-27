/* Reconstructed FUN_0002563c @ 0x2563c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_0007ca18(int,int);
int FUN_0002563c(int param_1)
{
    volatile int *piVar1 = (volatile int*)0x20007a44UL;
    if (param_1 == 0 || *piVar1 == 0) {
        DEBUG_PRINT(0x0009f1af);
        return -1;
    }
    int iVar3 = 10;
    int iVar2;
    do {
        iVar2 = FUN_0007ca18(*piVar1, param_1);
        if (iVar2 == 0) {
            return 0;
        }
        iVar3 = iVar3 - 1;
    } while (iVar3 != 0);
    return iVar2;
}

