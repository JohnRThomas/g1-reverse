/* Reconstructed FUN_0007c0e2 @ 0x7c0e2  (parity: 300/300 trials, PROVEN) */

extern int FUN_000181fc(void);
extern int FUN_00018e48(void *p);
extern void FUN_00072880(unsigned int a);

void FUN_0007c0e2(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int local_18 = param_1;
  unsigned int local_14 = param_2;
  unsigned int uStack_10 = param_3;
  (void)uStack_10;
  int iVar1 = FUN_000181fc();
  local_14 = (local_14 & 0xffffff00u) | 2u;
  (void)local_14;
  local_18 = param_1;
  int iVar2 = FUN_00018e48(&local_18);
  if (iVar2 == 0) {
    FUN_00072880((unsigned int)iVar1 + 0x200);
  }
}

