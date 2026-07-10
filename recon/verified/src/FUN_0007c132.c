/* Reconstructed FUN_0007c132 @ 0x7c132  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(void);
extern int FUN_00086be4(int a, void *b, int c);

int FUN_0007c132(unsigned int param_1, unsigned int param_2)
{
  unsigned char buf[8];
  int iVar1;
  int i;
  buf[7] = (unsigned char)(param_2 >> 24);
  for (i = 0; i < 7; i++) buf[i] = 0;
  iVar1 = FUN_000167a8();
  iVar1 = FUN_00086be4(iVar1 + 0x1069, buf, 7);
  if (iVar1 != 0) {
    for (i = 0; i < 7; i++) buf[i] = 0xff;
    iVar1 = FUN_000167a8();
    iVar1 = FUN_00086be4(iVar1 + 0x1069, buf, 7);
    if (iVar1 != 0) iVar1 = 1;
  }
  return iVar1;
}

