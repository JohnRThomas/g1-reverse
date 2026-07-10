/* net-core FUN_01032908 @ 0x1032908  (parity 300 trials PROVEN) */

extern void FUN_010218e4(void);
extern void FUN_010218d8(void);
extern void FUN_01033ca4(void);
extern void FUN_010218f0(unsigned int a);
extern void FUN_010218b4(void);

void FUN_01032908(void)
{
  volatile unsigned int * const *pp = (volatile unsigned int * const *)0x21000698;
  *(volatile unsigned int *)((*pp) + (0x10/4)) = 1;
  FUN_010218e4();
  FUN_010218d8();
  FUN_01033ca4();
  FUN_010218f0(3);
  FUN_010218b4();
  return;
}

