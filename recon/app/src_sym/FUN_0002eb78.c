/* Reconstructed FUN_0002eb78 @ 0x2eb78  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
unsigned int FUN_0002eb78(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned char bVar1 = *(volatile unsigned char *)(0x20018da6UL + 1);
  unsigned int uVar3 = bVar1;
  if (*(volatile unsigned char *)0x20018da4UL != uVar3) {
    DEBUG_PRINT(0xa3e9fUL, uVar3, param_3, (unsigned int)(*(volatile unsigned char *)0x20018da4UL), param_4);
  }
  *(volatile unsigned char *)0x20018da4UL = bVar1;
  return uVar3;
}

