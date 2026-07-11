/* Reconstructed FUN_000875e4 @ 0x875e4  (parity: 300/300 trials, PROVEN) */
extern unsigned long long FUN_00078c44(int, int*);
extern unsigned long long FUN_0000db4c(int, int, int, int);

double FUN_000875e4(int param_1, int param_2)
{
  unsigned long long uVar4, uVar5;
  int iVar2, iVar3, iVar1;

  uVar4 = FUN_00078c44(param_1, (int*)0x2007EFF4UL);
  iVar2 = (int)(uVar4 >> 32);
  uVar5 = FUN_00078c44(param_2, (int*)0x2007EFF8UL);
  iVar3 = (int)(uVar5 >> 32);
  iVar1 = (*(volatile int*)0x2007EFF4UL - *(volatile int*)0x2007EFF8UL) +
          (*(volatile int*)(param_1 + 0x10) - *(volatile int*)(param_2 + 0x10)) * 0x20;
  if (iVar1 < 1) {
    iVar3 = iVar3 + iVar1 * -0x100000;
  } else {
    iVar2 = iVar2 + iVar1 * 0x100000;
  }
  uVar4 = FUN_0000db4c((int)uVar4, iVar2, (int)uVar5, iVar3);
  union { unsigned long long bits; double value; } result = { uVar4 };
  return result.value;
}
