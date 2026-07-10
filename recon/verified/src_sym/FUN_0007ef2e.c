/* Reconstructed FUN_0007ef2e @ 0x7ef2e  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0007ef2e(unsigned char *param_1) {
  unsigned int v = *(unsigned int*)(param_1 + 0x14);
  if (v != 0) {
    v = *(volatile unsigned int*)(v + 4) & 1;
  }
  return v;
}

