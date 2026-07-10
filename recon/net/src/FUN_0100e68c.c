/* net-core FUN_0100e68c @ 0x100e68c  (parity 300 trials PROVEN) */

void FUN_0100e68c(int param_1, unsigned int param_2) {
    *(volatile char *)(param_1 + 0xb) = (char)param_2;
    *(volatile char *)(param_1 + 0xc) = (char)(param_2 >> 8);
}

