/* net-core FUN_0102a448 @ 0x102a448  (parity 300 trials PROVEN) */

extern void FUN_0103b53a(unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int FUN_0102a448(unsigned int param_1, unsigned int param_2) {
  FUN_0103b53a(0x21004b9f, param_1, param_2, 0xfc);
  *(volatile unsigned int *)0x210045e4 = param_2;
  return 0;
}

