/* Reconstructed FUN_00065d3c @ 0x65d3c  (parity: 300/300 trials, PROVEN) */

extern void FUN_000500ac(int);
extern void FUN_0007e2fa(unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_0007e2ec(unsigned int, unsigned int);

unsigned int FUN_00065d3c(unsigned int param_1, int param_2, int param_3)
{
  unsigned int uVar2;
  if (param_2 == 0) {
    FUN_0007e2fa(0x00099cbdU, 0x000f6e32U, 0x000f6bc5U, 0x34U);
    (void)FUN_0007e2ec(0x000f6bc5U, 0x34U);
  }
  {
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
}
