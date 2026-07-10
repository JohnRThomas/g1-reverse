/* Reconstructed FUN_000165b4 @ 0x165b4  (parity: 300/300 trials, PROVEN) */

int FUN_000165b4(void) {
  int a = *(volatile int*)(0x2007fc00UL + 0x64);
  int b = *(volatile int*)0x12345678UL;
  int r = a - b;
  if (r != 0) r = -1;
  return r;
}

