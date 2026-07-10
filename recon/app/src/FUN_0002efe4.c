/* Reconstructed FUN_0002efe4 @ 0x2efe4  (parity: 300/300 trials, PROVEN) */

extern void *FUN_000167a8(void);

unsigned int FUN_0002efe4(int param_1)
{
  unsigned char *pcVar1;

  pcVar1 = (unsigned char *)FUN_000167a8();
  if (*pcVar1 == 1) {
    if (param_1 == 0) {
      *(volatile unsigned char*)0x2000302fUL = 0;
    }
    else {
      *(volatile unsigned char*)0x2000302fUL = 2;
    }
  }
  return 0;
}

