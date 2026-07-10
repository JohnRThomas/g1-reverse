/* net-core FUN_0100e7c0 @ 0x100e7c0  (parity 300 trials PROVEN) */

void FUN_0100e7c0(int param_1, unsigned int param_2) {
    *(char *)(param_1 + 8) = (char)param_2;
    *(char *)(param_1 + 9) = (char)(param_2 >> 8);
}

