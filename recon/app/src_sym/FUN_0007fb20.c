/* Reconstructed FUN_0007fb20 @ 0x7fb20  (parity: 300/300 trials, PROVEN) */

extern int FUN_0007f98a(unsigned int, unsigned int, void *, unsigned int, unsigned int);

void FUN_0007fb20(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned char local_c;
  volatile unsigned int uStack_8;
  uStack_8 = param_3;
  local_c = (unsigned char)((param_2 & 3) << 6);
  FUN_0007f98a(param_1, 1, &local_c, 1, param_1);
  return;
}

