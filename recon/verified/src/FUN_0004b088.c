/* Reconstructed FUN_0004b088 @ 0x4b088  (parity: 300/300 trials, PROVEN) */

extern long long FUN_0004b01c(void);
extern void FUN_000723b8(int a, int b, int c, int d);
extern void thunk_FUN_00072558(int a);
typedef unsigned int (*fnptr4b088)(unsigned int, unsigned int, unsigned int);

unsigned int FUN_0004b088(int param_1, unsigned int param_2, unsigned int param_3)
{
  long long uVar4;
  int iVar1;
  unsigned int uVar2;
  int iVar3;

  uVar4 = FUN_0004b01c();
  iVar1 = 0x20002548;
  if ((int)uVar4 < 0) {
    uVar2 = 0xffffffff;
  } else {
    param_1 = param_1 * 0x28;
    iVar3 = param_1 + 0xc + iVar1;
    FUN_000723b8(iVar3, (int)(uVar4 >> 32), -1, -1);
    fnptr4b088 f = *(volatile fnptr4b088*)(*(volatile unsigned int*)(iVar1 + param_1 + 4));
    uVar2 = f(*(volatile unsigned int*)(iVar1 + param_1), param_2, param_3);
    thunk_FUN_00072558(iVar3);
  }
  return uVar2;
}

