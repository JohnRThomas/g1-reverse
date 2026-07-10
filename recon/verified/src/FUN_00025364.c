/* Reconstructed FUN_00025364 @ 0x25364  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(void);
unsigned int FUN_00025364(void)
{
  unsigned int uVar2;
  if (*(volatile unsigned int *)0x20007a24UL <= 0x13ec) {
    uVar2 = 2;
  } else {
    int iVar1 = FUN_000167a8();
    if (*(volatile unsigned char *)(iVar1 + 0xfc0) < 100) {
      uVar2 = 0;
    } else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

