/* Reconstructed FUN_000787bc @ 0x787bc  (parity: 300/300 trials, PROVEN) */

extern int FUN_000785d4(int a, int b);
extern int FUN_00076a94(int a, int b, int c, int d);
void FUN_000787bc(int param_1, int param_2)
{
  int iVar1;
  iVar1 = FUN_000785d4(param_1, 1);
  if (iVar1 == 0) {
    iVar1 = FUN_00076a94(0x000f8cd5, 0x140, 0, 0x000f8c42);
  }
  *(volatile int *)(iVar1 + 0x14) = param_2;
  *(volatile int *)(iVar1 + 0x10) = 1;
}

