/* Reconstructed get_usage @ 0x7e33a  (parity: 300/300 trials, PROVEN) */

extern int free_space(int a, int *b, int c, int d, int e);
int get_usage(int param_1, int param_2, int param_3, int param_4)
{
  int iVar1;
  int local_c;
  local_c = param_2;
  iVar1 = free_space(param_1, &local_c, param_3, param_4, param_1);
  if (iVar1 != 0) {
    local_c = local_c - 1 + *(volatile int *)(param_1 + 0xc);
  }
  return (*(volatile int *)(param_1 + 0x24) - local_c) - 1;
}

