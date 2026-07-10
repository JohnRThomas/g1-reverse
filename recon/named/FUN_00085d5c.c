/* named: FUN_00085d5c */
/* Reconstructed FUN_00085d5c @ 0x85d5c  (parity: 300/300 trials, PROVEN) */

int FUN_00085d5c(int param_1)
{
    if (param_1 != 0 && *(char *)(param_1 + 0x10) != 0) {
        return *(int *)(param_1 + 0xc) == 0;
    }
    return 1;
}

