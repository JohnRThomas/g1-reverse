/* Reconstructed FUN_0007dac0 @ 0x7dac0  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004a5b0(void);
extern int FUN_000167a8(void);
unsigned char FUN_0007dac0(void)
{
  unsigned char uVar1;
  int iVar2;
  iVar2 = FUN_0004a5b0();
  if (iVar2 == 0) {
    iVar2 = FUN_000167a8();
    uVar1 = *(volatile unsigned char *)(iVar2 + 0x10db);
  } else {
    uVar1 = 7;
  }
  return uVar1;
}

