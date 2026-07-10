/* net-core FUN_0101fc40 @ 0x101fc40  (parity 300 trials PROVEN) */

extern void FUN_01020088(unsigned int);

void FUN_0101fc40(unsigned int param_1, unsigned int param_2, int param_3)
{
  FUN_01020088(2);
  *(volatile unsigned char*)0x210014d8 = 1;
  *(volatile int*)(0x4100e000 + 0x510) = param_3 - 3;
  *(volatile unsigned int*)(0x4100e000 + 0x508) = param_1;
  *(volatile unsigned int*)(0x4100e000 + 0x504) = param_2;
}

