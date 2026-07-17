/* Reconstructed FUN_00047ab8 @ 0x47ab8  (parity: 300/300 trials, PROVEN) */

extern void FUN_00076d7c(unsigned int);

void FUN_00047ab8(void)
{
  volatile int *piVar1 = (volatile int *)0x20009fccUL;
  int value = *piVar1;
  if (value != 0) {
    FUN_00076d7c((unsigned int)value);
    *piVar1 = 0;
  }
}
