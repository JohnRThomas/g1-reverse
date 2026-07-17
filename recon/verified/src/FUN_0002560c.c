/* Reconstructed FUN_0002560c @ 0x2560c  (parity: 300/300 trials, PROVEN) */

extern int FUN_000330a8(unsigned int a0);
extern int FUN_000330ec(void);
extern void DEBUG_PRINT(unsigned int a0);

int FUN_0002560c(void)
{
  int iVar1;
  volatile unsigned int *volatile state = (volatile unsigned int *)0x20007a44UL;
  iVar1 = FUN_000330a8(*state);
  if (iVar1 == 0) {
    iVar1 = FUN_000330ec();
    if (iVar1 != 0) { iVar1 = -2; }
  } else {
    DEBUG_PRINT(0x0009f196);
    iVar1 = -1;
  }
  return iVar1;
}
