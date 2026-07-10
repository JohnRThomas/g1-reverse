/* Reconstructed FUN_0007c968 @ 0x7c968  (parity: 300/300 trials, PROVEN) */

extern int FUN_000257ec(unsigned int, unsigned int, void *, unsigned int, unsigned int);

int FUN_0007c968(unsigned int param_1, unsigned int *param_2, unsigned int param_3)
{
  int iVar1;
  unsigned short local_14 = 0;
  if (param_2 == 0) {
    iVar1 = -0x16;
  } else {
    iVar1 = FUN_000257ec(param_1, 0x14, &local_14, 2, param_1);
    if (iVar1 == 0) {
      *(unsigned short *)((char *)param_2 + 2) = local_14;
      iVar1 = FUN_000257ec(param_1, 0x16, (void *)param_2, 1, param_1);
    }
  }
  return iVar1;
}

