/* net-core FUN_0102ece0 @ 0x102ece0  (parity 300 trials PROVEN) */

void FUN_0102ece0(int param_1, unsigned int param_2, int param_3, unsigned int param_4,
                   unsigned int param_5, unsigned int param_6, unsigned int param_7)
{
  *(unsigned int*)(param_3 - 0x20) = param_4;
  unsigned int uVar1 = 0x0102cc3d;
  *(unsigned int*)(param_3 - 0x1c) = param_5;
  *(unsigned int*)(param_3 - 0x18) = param_6;
  *(unsigned int*)(param_3 - 8) = uVar1 & 0xfffffffe;
  *(unsigned int*)(param_3 - 0x14) = param_7;
  *(unsigned int*)(param_3 - 4) = 0x1000000;
  *(int*)(param_1 + 0x50) = param_3 - 0x20;
  *(unsigned int*)(param_1 + 0x8c) = 0;
}

