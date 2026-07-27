/* Reconstructed FUN_0005ee6c @ 0x5ee6c  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2fa(unsigned long, ...);
extern int FUN_0007e2ec(unsigned int, unsigned int);

void FUN_0005ee6c(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar1;
  int fakeParam1;
  if (*(char *)(param_1 + 9) == 0) {
    if (*(int *)(param_1 + 4) == 0) {
      *(unsigned short *)(param_1 + 0x10) = 0;
      *(unsigned int *)(param_1 + 0xc) = *(unsigned int *)(param_1 + 0x14);
      return;
    }
    FUN_0007e2fa(0x99cbd, 0xf53cf, 0xf539a, 0x5b, param_4);
    uVar1 = 0x5b;
  } else {
    FUN_0007e2fa(0x99cbd, 0xf53be, 0xf539a, 0x5a, param_4);
    uVar1 = 0x5a;
  }
  fakeParam1 = FUN_0007e2ec(0xf539a, uVar1);
  while (1) {
    if (*(int *)(fakeParam1 + 4) == 0) {
      *(unsigned short *)(fakeParam1 + 0x10) = 0;
      *(unsigned int *)(fakeParam1 + 0xc) = *(unsigned int *)(fakeParam1 + 0x14);
      return;
    }
    FUN_0007e2fa(0x99cbd, 0xf53cf, 0xf539a, 0x5b, param_4);
    fakeParam1 = FUN_0007e2ec(0xf539a, 0x5b);
  }
}

