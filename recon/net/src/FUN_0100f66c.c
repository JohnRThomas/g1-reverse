/* net-core FUN_0100f66c @ 0x100f66c  (parity 300 trials PROVEN) */

int FUN_0100f66c(void)
{
  volatile unsigned int *p0  = (volatile unsigned int*)0x21000ef4;
  volatile unsigned int *p1  = (volatile unsigned int*)0x21000ef8;
  unsigned int uVar2, uVar3, uVar4;

  uVar3 = *p0;
  uVar4 = *p1 ^ uVar3;
  uVar2 = uVar3 * 0x9e3779bbu;
  *p0 = uVar4 ^ ((uVar3 >> 6) | (uVar3 << 0x1a)) ^ (uVar4 << 9);
  *p1 = (uVar4 >> 0x13) | (uVar4 << 0xd);
  return (int)(((uVar2 >> 0x1b) | (uVar2 << 5)) * 5);
}

