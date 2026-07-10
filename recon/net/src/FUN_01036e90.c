/* net-core FUN_01036e90 @ 0x1036e90  (parity 300 trials PROVEN) */

unsigned int FUN_01036e90(int param_1)
{
  unsigned int uVar1;

  if (*(volatile unsigned short *)(param_1 + 0xe) < 0x80) {
    uVar1 = *(volatile unsigned int *)0x21004b64u;
    if (uVar1 == 0) goto done;
    if ((*(volatile int *)0x21004b60u <= (int)*(volatile signed char *)(param_1 + 0xe)) &&
        ((*(volatile unsigned char *)(param_1 + 0xd) & 0x1f) == 0)) {
      uVar1 = (unsigned int)param_1 - 0x210043a8u;
      if (uVar1 != 0) {
        uVar1 = 1;
      }
      goto done;
    }
  }
  uVar1 = 0;
done:
  return uVar1 & 1;
}

