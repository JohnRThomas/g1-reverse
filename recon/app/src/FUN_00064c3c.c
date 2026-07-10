/* Reconstructed FUN_00064c3c @ 0x64c3c  (parity: 300/300 trials, PROVEN) */

extern int FUN_00084fd4(unsigned int);
void FUN_00064c3c(int param_1)
{
  int iVar1;
  unsigned int uVar2;
  iVar1 = FUN_00084fd4(*(volatile unsigned int *)0x20002bacUL);
  if (iVar1 != 0) {
    if (param_1 == 0) {
      uVar2 = 1;
    } else {
      uVar2 = 2;
    }
    *(volatile unsigned int *)(iVar1 + 0xc) = uVar2;
  }
}

