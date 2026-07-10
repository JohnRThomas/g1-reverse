/* net-core FUN_0100cc00 @ 0x100cc00  (parity 300 trials PROVEN) */

int FUN_0100cc00(unsigned int param_1) {
  unsigned int base = 0x21000d18;
  if (param_1 < *(volatile unsigned char *)(base + 1)) {
    return *(volatile unsigned char *)(param_1 + base + 0x13a) == 0;
  }
  return 0;
}

