/* Reconstructed FUN_0007d248 @ 0x7d248  (parity: 300/300 trials, PROVEN) */

extern char *FUN_000167a8(void);

int FUN_0007d248(void)
{
  char *iVar1;
  int uVar2;
  iVar1 = FUN_000167a8();
  if ((unsigned char)iVar1[0xfc0] < 0x15) {
    uVar2 = 0;
  } else {
    iVar1 = FUN_000167a8();
    if ((unsigned char)iVar1[0xfc1] < 0x15) {
      iVar1 = FUN_000167a8();
      uVar2 = -1;
      if (2 < (unsigned char)iVar1[0xfc1]) uVar2 = 0;
    } else {
      uVar2 = -1;
    }
  }
  return uVar2;
}

