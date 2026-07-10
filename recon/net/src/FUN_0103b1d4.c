/* net-core FUN_0103b1d4 @ 0x103b1d4  (parity 300 trials PROVEN) */

void FUN_0103b1d4(int param_1)
{
    *(int *)param_1 = param_1;
    *(int *)(param_1 + 4) = param_1;
    *(unsigned int *)(param_1 + 8) = 0;
    *(unsigned int *)(param_1 + 0xc) = 0;
}

