/* named: double_is_unordered */
/* Reconstructed double_is_unordered @ 0xde2c  (parity: 300/300 trials, PROVEN) */

int double_is_unordered(int param_1, unsigned int param_2, int param_3, unsigned int param_4)
{
    if ((((int)(param_2 << 1) >> 21) != -1 || (param_1 == 0 && (param_2 & 0xfffff) == 0)) &&
        (((int)(param_4 << 1) >> 21) != -1 || (param_3 == 0 && (param_4 & 0xfffff) == 0))) {
        return 0;
    }
    return 1;
}

