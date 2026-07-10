/* Reconstructed FUN_0007e4f2 @ 0x7e4f2  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0007e33a(void);
void FUN_0007e4f2(int param_1)
{
  unsigned int uVar1;
  unsigned int uVar2;
  if ((*(volatile int *)(param_1 + 0x10) << 0x1d) < 0) {
    uVar2 = *(volatile unsigned int *)(param_1 + 0x28);
    uVar1 = FUN_0007e33a();
    if (uVar1 <= uVar2) {
      *(volatile unsigned int *)(param_1 + 0x28) = uVar2;
    }
    if (uVar1 > uVar2) {
      *(volatile unsigned int *)(param_1 + 0x28) = uVar1;
    }
  }
}

