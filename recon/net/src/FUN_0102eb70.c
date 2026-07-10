/* net-core FUN_0102eb70 @ 0x102eb70  (parity 300 trials PROVEN) */

volatile unsigned int *DAT_0102eb88 = (volatile unsigned int *)0xe000e100;
unsigned int FUN_0102eb70(unsigned int param_1) {
  return (1u << (param_1 & 0x1f)) & DAT_0102eb88[param_1 >> 5];
}

