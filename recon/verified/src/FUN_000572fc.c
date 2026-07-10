/* Reconstructed FUN_000572fc @ 0x572fc  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_000572fc(int *param_1)
{
    if (param_1 != (int*)0) {
        if (*(volatile int*)0x2000ad28UL != 0) {
            return 0xffffff88;
        }
        if (param_1[4] == 0 &&
            (param_1[0] != 0 || param_1[1] != 0 || param_1[2] != 0 || param_1[5] != 0)) {
            return 0xffffffea;
        }
    }
    *(volatile int*)0x2000ad28UL = (int)param_1;
    return 0;
}

