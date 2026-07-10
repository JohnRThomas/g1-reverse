/* net-core FUN_0100e714 @ 0x100e714  (parity 300 trials PROVEN) */

void FUN_0100e714(int param_1, unsigned int *param_2)
{
  *param_2 = *(unsigned int *)(param_1 + 4);
  *((unsigned char *)param_2 + 4) = *(unsigned char *)(param_1 + 8);
}

