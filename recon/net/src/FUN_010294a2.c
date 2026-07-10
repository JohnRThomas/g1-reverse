/* net-core FUN_010294a2 @ 0x10294a2  (parity 300 trials PROVEN) */

extern unsigned int FUN_0102946c(unsigned short, unsigned char);

unsigned int FUN_010294a2(volatile unsigned short *param_1, volatile unsigned short *param_2)
{
  unsigned short uVar2 = *param_1;
  *param_2 = uVar2;
  unsigned char cVar1 = *((volatile unsigned char *)param_1 + 2);
  return FUN_0102946c(uVar2, cVar1);
}

