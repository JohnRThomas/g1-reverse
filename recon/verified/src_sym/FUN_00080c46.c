/* Reconstructed FUN_00080c46 @ 0x80c46  (parity: 300/300 trials, PROVEN) */

extern int FUN_000527dc(unsigned long);
extern long long FUN_0008157a(unsigned int);
extern void FUN_0007350c(unsigned int, unsigned int, unsigned int, unsigned int);
extern void FUN_00073518(int);

void FUN_00080c46(unsigned int param_1)
{
  int iVar1;
  long long uVar2;
  iVar1 = FUN_000527dc(param_1);
  if (iVar1 == 0) return;
  uVar2 = FUN_0008157a(param_1);
  if ((int)uVar2 != 0 && (int)uVar2 != -0x78) {
    FUN_0007350c(iVar1 + 0x38, (int)(uVar2 >> 32), 0x8000, 0);
    return;
  }
  FUN_00073518(iVar1 + 0x38);
}

