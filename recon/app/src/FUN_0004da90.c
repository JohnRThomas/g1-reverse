/* Reconstructed FUN_0004da90 @ 0x4da90  (parity: 300/300 trials, PROVEN) */

extern void FUN_0004da6c(unsigned int param_1, unsigned int param_2);

void FUN_0004da90(unsigned int param_1, int param_2)
{
    unsigned int uVar1;
    if ((int)((unsigned int)param_2 << 0x1b) < 0) {
        return;
    }
    uVar1 = 0x000f5400;
    if ((int)((unsigned int)param_2 << 0x1a) < 0) {
        uVar1 = 0x000a8c94;
    }
    FUN_0004da6c(param_1, uVar1);
}

