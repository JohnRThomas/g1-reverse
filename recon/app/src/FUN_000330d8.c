/* Reconstructed FUN_000330d8 @ 0x330d8  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007c8c4(int);

unsigned int FUN_000330d8(void) {
  unsigned int value = *(volatile unsigned int *)0x20002424UL;
  if (value != 0) {
    FUN_0007c8c4((int)value);
  }
  return 0;
}
