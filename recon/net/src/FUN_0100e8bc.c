/* net-core FUN_0100e8bc @ 0x100e8bc  (parity 300 trials PROVEN) */

void FUN_0100e8bc(int param_1, unsigned int param_2) {
    *(char *)(param_1 + 6) = (char)param_2;
    *(char *)(param_1 + 7) = (char)(param_2 >> 8);
}

