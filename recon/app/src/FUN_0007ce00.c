/* Reconstructed FUN_0007ce00 @ 0x7ce00  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(void);

int FUN_0007ce00(void)
{
  int iVar1;
  iVar1 = FUN_000167a8();
  if (*(volatile int*)(*(volatile int*)(iVar1+0x1054)) == 0) {
    iVar1 = FUN_000167a8();
    if (*(volatile unsigned char*)(*(volatile int*)(iVar1+0x1054)+4) == 1) {
      iVar1 = FUN_000167a8();
      if (*(volatile unsigned char*)(iVar1+0xd5) == 0) {
        iVar1 = FUN_000167a8();
        return *(volatile unsigned char*)(iVar1+0xfe6) == 1;
      }
    }
  }
  return 0;
}

