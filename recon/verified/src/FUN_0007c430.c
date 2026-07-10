/* Reconstructed FUN_0007c430 @ 0x7c430  (parity: 300/300 trials, PROVEN) */

unsigned int FUN_0007c430(unsigned char *param_1, unsigned int param_2, int *param_3)
{
  if (param_1 != 0 && param_3 != 0 &&
      (*param_3 != 0 || ((char)((unsigned char*)param_3)[4] == 0))) {
    *param_1 = *param_1 | (param_2 & 7);
    param_1[1] = ((unsigned char*)param_3)[4];
    *(int *)(param_1 + 4) = *param_3;
    return 0;
  }
  return 7;
}

