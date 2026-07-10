/* Reconstructed FUN_0002ea78 @ 0x2ea78  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083dc8(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
extern void DEBUG_PRINT(unsigned int a0);

unsigned int FUN_0002ea78(void)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int base = *(volatile unsigned int*)(0x00087ce0UL + 4);
  iVar1 = FUN_00083dc8(*(volatile unsigned int*)(base + 0x1c), 3, 0xc, 8);
  if (iVar1 < 0) {
    DEBUG_PRINT(0x000a3e1a);
    uVar2 = 0xffffffff;
  } else {
    uVar2 = 0;
  }
  return uVar2;
}

