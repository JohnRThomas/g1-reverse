/* Reconstructed FUN_0004a16c @ 0x4a16c  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007d894(void *dst, void *src, int n);
extern void FUN_0007d8f4(void *dst, void *src, int n);

void FUN_0004a16c(int *param_1, void *param_2)
{
  unsigned int uVar1;
  int iVar2;
  unsigned char localBuf[8];

  uVar1 = ((unsigned int)*param_1 >> 3) & 0x3f;
  if (uVar1 < 0x38) {
    iVar2 = 0x38 - uVar1;
  } else {
    iVar2 = 0x78 - uVar1;
  }
  FUN_0007d894(localBuf, param_1, 8);
  FUN_0007d8f4(param_1, (void*)0x200034f7UL, iVar2);
  FUN_0007d8f4(param_1, localBuf, 8);
  FUN_0007d894(param_2, (char*)param_1+8, 0x10);
  return;
}

