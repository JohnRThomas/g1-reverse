/* net-core FUN_01039bfe @ 0x1039bfe  (parity 300 trials PROVEN) */

extern int FUN_01039bd8(int a, int *b, unsigned int c, unsigned int d);

int FUN_01039bfe(int param_1, int param_2, unsigned int param_3, unsigned int param_4)
{
  int local_c = param_2;
  int iVar1 = FUN_01039bd8(param_1, &local_c, param_3, param_4);
  if (iVar1 != 0) {
    local_c = local_c - 1 + *(int*)(param_1 + 0xc);
  }
  return *(int*)(param_1 + 0x24) - local_c - 1;
}

