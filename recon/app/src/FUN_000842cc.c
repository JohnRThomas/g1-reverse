/* Reconstructed FUN_000842cc @ 0x842cc  (parity: 300/300 trials, PROVEN) */

extern int FUN_00062070(unsigned int, unsigned int, void *, unsigned int, int);
extern int FUN_00083dc8(unsigned int, int, unsigned int, unsigned char);

void FUN_000842cc(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int uStack_14;
  unsigned int uStack_10;
  uStack_14 = param_2;
  uStack_10 = param_3;
  iVar1 = FUN_00062070(param_3, param_4, (unsigned char *)&uStack_14 + 2, param_4, param_1);
  if (iVar1 != -0x16) {
    FUN_00083dc8(*(unsigned int *)(param_1 + 0x1c), 8, (param_2 + 0xc) & 0xff, *((unsigned char *)&uStack_14 + 2));
  }
}

