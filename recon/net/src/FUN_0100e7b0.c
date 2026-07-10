/* net-core FUN_0100e7b0 @ 0x100e7b0  (parity 300 trials PROVEN) */

void FUN_0100e7b0(int param_1, unsigned int param_2) {
    *(char *)(param_1 + 4) = (char)param_2;
    *(char *)(param_1 + 5) = (char)(param_2 >> 8);
}

