/* Reconstructed FUN_000469a8 @ 0x469a8  (parity: 300/300 trials, PROVEN) */

int FUN_000469a8(unsigned int param_1) {
  unsigned int idx = param_1 - 1;
  if (idx <= 0xf) {
    return (int)*(volatile signed char*)(0x000bc073UL + idx);
  }
  return -1;
}

