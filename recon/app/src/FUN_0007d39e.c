/* Reconstructed FUN_0007d39e @ 0x7d39e  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(void);
void FUN_0007d39e(void)
{
  int iVar1;
  iVar1 = FUN_000167a8();
  if (**(volatile char **)(iVar1 + 0x1014) != (char)0) {
    iVar1 = FUN_000167a8();
    **(volatile unsigned char **)(iVar1 + 0x1014) = 0;
  }
  return;
}

