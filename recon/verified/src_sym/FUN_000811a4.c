/* Reconstructed FUN_000811a4 @ 0x811a4  (parity: 300/300 trials, PROVEN) */

extern void atomic_and_1(unsigned int*, unsigned int);
void FUN_000811a4(unsigned int *param_1, unsigned int param_2, int param_3)
{
    unsigned int uVar1 = 1u << (param_2 & 0xff);
    if (param_3 == 0) {
        atomic_and_1(param_1, ~uVar1);
        return;
    }
    *param_1 = *param_1 | uVar1;
}

