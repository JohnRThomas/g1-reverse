/* Reconstructed FUN_00086cb6 @ 0x86cb6  (parity: 300/300 trials, PROVEN) */

extern int FUN_00086c88(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);

int FUN_00086cb6(unsigned int param_1, unsigned int param_2, unsigned char *param_3, int param_4)
{
  int iVar1;
  unsigned char *puVar2 = param_3 + param_4;
  int iVar3 = param_4;
  while (1) {
    if (param_3 == puVar2) {
      return 0;
    }
    iVar1 = FUN_00086c88(param_1, *param_3, param_2, param_4, iVar3);
    param_4 = iVar1 + 1;
    param_3 = param_3 + 1;
    if (param_4 == 0) break;
  }
  return iVar1;
}

