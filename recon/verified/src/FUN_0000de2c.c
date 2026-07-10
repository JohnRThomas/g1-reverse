/* Reconstructed FUN_0000de2c @ 0xde2c  (parity: 300/300 trials, PROVEN) */

int FUN_0000de2c(int param_1, unsigned int param_2, int param_3, unsigned int param_4)
{
    if ((((int)(param_2 << 1) >> 21) != -1 || (param_1 == 0 && (param_2 & 0xfffff) == 0)) &&
        (((int)(param_4 << 1) >> 21) != -1 || (param_3 == 0 && (param_4 & 0xfffff) == 0))) {
        return 0;
    }
    return 1;
}

