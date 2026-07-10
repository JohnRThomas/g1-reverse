/* Reconstructed FUN_00083ba6 @ 0x83ba6  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083dba(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

int FUN_00083ba6(int param_1, unsigned int *param_2)
{
  int iVar1;
  unsigned int uStack_c = (unsigned int)param_2;
  iVar1 = FUN_00083dba(*(volatile unsigned int *)((unsigned int)(*(volatile unsigned int *)((unsigned int)param_1 + 4)) + 4), 6, 0x1e, (unsigned int)&uStack_c + 3, (unsigned int)param_1);
  if (iVar1 >= 0) {
    iVar1 = 0;
    *param_2 = uStack_c >> 0x18;
  }
  return iVar1;
}

