/* Reconstructed FUN_0005fb30 @ 0x5fb30  (parity: 300/300 trials, PROVEN) */

extern int FUN_00066214(void);
extern void FUN_000837a2(unsigned int a, unsigned int b, void *c);
extern void FUN_0004ba38(unsigned int a);

unsigned int FUN_0005fb30(unsigned int *param_1)
{
  unsigned int uVar1;
  unsigned int local_20;
  unsigned int local_1c;
  int iStack_18;

  iStack_18 = FUN_00066214();
  if (iStack_18 == 0x0bad0000) {
    uVar1 = 0;
  } else {
    local_1c = 0xf5692;
    local_20 = 3;
    FUN_000837a2(0x881a0, 0x1840, &local_20);
    if ((int)((unsigned int)*(volatile unsigned char *)((char*)param_1 + 0x50) << 0x1f) < 0) {
      FUN_0004ba38(*param_1);
    }
    uVar1 = 0xfffffffb;
    *(volatile unsigned char *)((char*)param_1 + 0x51) = 0;
  }
  return uVar1;
}

