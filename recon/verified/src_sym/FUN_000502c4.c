/* Reconstructed arch_new_thread @ 0x502c4  (parity: 300/300 trials, PROVEN) */

void arch_new_thread(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
  unsigned int uVar1;
  *(int*)(param_3 - 0x20) = param_4;
  uVar1 = 0x0007ddd9 & 0xfffffffe;
  *(int*)(param_3 - 0x1c) = param_5;
  *(int*)(param_3 - 0x18) = param_6;
  *(unsigned int*)(param_3 - 8) = uVar1;
  *(int*)(param_3 - 0x14) = param_7;
  *(int*)(param_3 - 4) = 0x1000000;
  *(int*)(param_1 + 0x8c) = 0;
  *(int*)(param_1 + 0x50) = param_3 - 0x20;
  *(int*)(param_1 + 0xd4) = 0xfd00;
}

