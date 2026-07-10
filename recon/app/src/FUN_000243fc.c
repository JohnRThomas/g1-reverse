/* Reconstructed FUN_000243fc @ 0x243fc  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_00072240(unsigned int, void *, unsigned int, unsigned int);

unsigned int FUN_000243fc(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  unsigned int uVar2;
  int iVar3;
  unsigned int stk[3];

  uVar1 = 0x20003960UL;
  uVar2 = 0;
  stk[0] = param_1;
  stk[1] = param_2;
  stk[2] = param_3;
  for (iVar3 = *(volatile int *)(0x20003960UL + 0x24); iVar3 > 0; iVar3--) {
    uVar2 = FUN_00072240(uVar1, stk, 0, 0);
  }
  return uVar2;
}

