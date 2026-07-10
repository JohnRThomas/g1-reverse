/* Reconstructed FUN_0002eba0 @ 0x2eba0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
unsigned int FUN_0002eba0(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
  unsigned char bVar1 = *(volatile unsigned char *)(0x20018da6UL + 2);
  unsigned int uVar3 = bVar1;
  if (*(volatile unsigned char *)0x20018da3UL != uVar3) {
    DEBUG_PRINT(0xa3ec1UL, uVar3, param_3, (unsigned int)(*(volatile unsigned char *)0x20018da3UL), param_4);
  }
  *(volatile unsigned char *)0x20018da3UL = bVar1;
  return uVar3;
}

