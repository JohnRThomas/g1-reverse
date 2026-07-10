/* Reconstructed FUN_00085fa2 @ 0x85fa2  (parity: 300/300 trials, PROVEN) */

extern int FUN_00085f06(int, int);
extern void FUN_00085dc4(int, int);

int FUN_00085fa2(int param_1)
{
    int iVar1;
    iVar1 = FUN_00085f06(param_1, 5);
    if (iVar1 != 0) {
        if (*(char*)(param_1 + 0x10) != 0) {
            return iVar1;
        }
        if (*(unsigned int*)(param_1 + 8) < 0x7fffffffU) {
            *(unsigned int*)(param_1 + 8) = *(unsigned int*)(param_1 + 8) << 1;
            return iVar1;
        }
        FUN_00085dc4(param_1, 5);
    }
    return 0;
}

