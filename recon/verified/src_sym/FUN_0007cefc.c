/* Reconstructed FUN_0007cefc @ 0x7cefc  (parity: 300/300 trials, PROVEN) */

extern char *FUN_000232b8(void);

int FUN_0007cefc(void)
{
  char *iVar1;
  iVar1 = FUN_000232b8();
  if (iVar1[4] == (char)0x45 && iVar1[5] == (char)0x47 && iVar1[6] == (char)0x50) {
    if (iVar1[7] == (char)0x30) return 1;
    if (iVar1[7] == (char)0x31) {
      if ((unsigned char)(iVar1[8] - 0x30) < 4) return 1;
      return 0;
    }
  }
  return 0;
}

