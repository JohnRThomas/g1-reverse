/* net-core FUN_0100e72c @ 0x100e72c  (parity 300 trials PROVEN) */

void FUN_0100e72c(int param_1, unsigned int *param_2)
{
  unsigned int uVar1 = param_2[1];
  *(unsigned int *)(param_1 + 4) = *param_2;
  *(unsigned int *)(param_1 + 8) = uVar1;
}

