/* Reconstructed FUN_0007ef6e @ 0x7ef6e  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0007ef6e(unsigned char *param_1) {
  unsigned int v = *(unsigned int*)(param_1 + 0x14);
  if (v != 0) {
    unsigned int w = __atomic_load_n((unsigned int *)(v + 4), __ATOMIC_ACQUIRE);
    v = (w >> 6) & 1;
  }
  return v;
}
