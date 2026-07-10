/* Reconstructed FUN_00065d3c @ 0x65d3c  (parity: 300/300 trials, PROVEN) */

extern void FUN_000500ac(int);
extern int FUN_0007e2fa(void);
extern int FUN_0007e2ec(void);

unsigned int FUN_00065d3c(unsigned int param_1, int param_2, int param_3)
{
  unsigned int uVar2;
  if (param_2 != 0) {
    if (*(volatile unsigned char*)0x2000b328UL == 0) {
      FUN_000500ac(0x2a);
      uVar2 = 0x0bad0000;
      *(volatile unsigned char*)0x2000b328UL = 1;
      *(volatile int*)0x2000b324UL = param_2;
      *(volatile int*)0x2000b32cUL = param_3;
    } else {
      uVar2 = 0x0bad000c;
    }
    return uVar2;
  }
  FUN_0007e2fa();
  return FUN_0007e2ec();
}

