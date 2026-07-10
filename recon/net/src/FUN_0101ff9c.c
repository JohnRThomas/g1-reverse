/* net-core FUN_0101ff9c @ 0x101ff9c  (parity 300 trials PROVEN) */

extern void FUN_01008d00(unsigned int, unsigned int, unsigned int, unsigned int);

int FUN_0101ff9c(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  if (*(volatile unsigned char *)0x210014dcu == 0) {
    FUN_01008d00(0x3c, 0x274, param_3, param_4);
    FUN_01008d00(0x3c, 0x275, param_3, param_4);
    while (1) { FUN_01008d00(0x3c, 0x275, param_3, param_4); }
  }
  if (*(volatile int *)(0x4100e000u + 0x104) != 0) {
    int iVar1 = *(volatile int *)(0x4100e000u + 0x400);
    if (iVar1 != 0) {
      iVar1 = 1;
    }
    return iVar1;
  }
  FUN_01008d00(0x3c, 0x275, param_3, param_4);
  while (1) { FUN_01008d00(0x3c, 0x275, param_3, param_4); }
}

