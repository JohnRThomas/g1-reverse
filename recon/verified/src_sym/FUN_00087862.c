/* Reconstructed FUN_00087862 @ 0x87862  (parity: 300/300 trials, PROVEN) */

extern void FUN_00076d8c(void);
int FUN_00087862(int param_1, unsigned int *param_2)
{
  if (param_2[0xd] != 0) {
    if (param_2[0xd] != (unsigned int)(param_2 + 0x11)) {
      FUN_00076d8c();
    }
    param_2[0xd] = 0;
    param_2[1] = param_2[0x10];
    if (param_2[0x10] != 0) {
      *param_2 = param_2[0xf];
      return 0;
    }
  }
  *param_2 = param_2[4];
  param_2[1] = 0;
  *(unsigned short *)((char*)param_2 + 0xc) |= 0x20;
  return -1;
}

