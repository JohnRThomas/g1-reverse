/* Reconstructed FUN_00083bca @ 0x83bca  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083ba6(unsigned int a, unsigned int *b, unsigned int c, unsigned int d, unsigned int e);
extern void FUN_00083b62(unsigned int a, unsigned int b, unsigned int c);

void FUN_00083bca(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int local_14 = param_2;
  int iVar1 = FUN_00083ba6(param_1, &local_14, param_3, param_4, param_1);
  if (iVar1 >= 0) {
    FUN_00083b62(param_1, param_2, ~local_14);
  }
}

