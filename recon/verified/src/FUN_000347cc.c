/* Reconstructed FUN_000347cc @ 0x347cc  (parity: 300/300 trials, PROVEN) */

extern int FUN_000167a8(void);
extern unsigned int FUN_0007d224(void);

int FUN_000347cc(void)
{
  int iVar2;
  unsigned int uVar3;
  int r0;
  unsigned char b;
  unsigned int val;

  r0 = FUN_000167a8();
  b = *(volatile unsigned char*)(long)(r0 + 0xdd);
  iVar2 = *(volatile int*)(long)(0x20007dacUL + (unsigned int)(b - 1) * 0x1b4);
  if (iVar2 != 0) {
    uVar3 = FUN_0007d224();
    r0 = FUN_000167a8();
    b = *(volatile unsigned char*)(long)(r0 + 0xdd);
    val = *(volatile unsigned int*)(long)(0x20007dacUL + (unsigned int)(b - 1) * 0x1b4);
    if ((unsigned int)(val + 0xf) < uVar3) iVar2 = 2; else iVar2 = 1;
  }
  return iVar2;
}

