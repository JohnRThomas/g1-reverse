/* Reconstructed FUN_000406e4 @ 0x406e4  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(void);
extern void FUN_00086c78(unsigned int, unsigned int, unsigned int);

unsigned int FUN_000406e4(void)
{
  int iVar1;

  iVar1 = FUN_000167a8();
  FUN_00086c78(*(unsigned int *)(iVar1 + 0x1014),0,0x21);
  *(volatile unsigned char*)0x2001cdd3UL = 1;
  return 0;
}

