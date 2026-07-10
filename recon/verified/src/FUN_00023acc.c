/* Reconstructed FUN_00023acc @ 0x23acc  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00072240(unsigned int, void *, unsigned int, unsigned int);

unsigned int FUN_00023acc(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int p4, unsigned int p5, unsigned int p6, unsigned int p7, int count)
{
  unsigned int uVar1;
  unsigned int uVar2;
  unsigned int stk[3];

  uVar1 = 0x20003994UL;
  uVar2 = 0;
  stk[0] = param_1;
  stk[1] = param_2;
  stk[2] = param_3;
  for (; count > 0; count--) {
    uVar2 = FUN_00072240(uVar1, stk, 0, 0);
  }
  return uVar2;
}

