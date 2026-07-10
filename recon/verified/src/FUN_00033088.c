/* Reconstructed FUN_00033088 @ 0x33088  (parity: 300/300 trials, PROVEN) */

int FUN_00033088(int param_1)
{
  int iVar1 = 0x20002424;
  if (param_1 != 0) {
    if (*(volatile int *)(0x20002424UL + 4) != param_1) {
      *(volatile int *)(0x20002424UL + 4) = param_1;
    }
    *(volatile unsigned char *)(iVar1 + 8) = 1;
    return 0;
  }
  return -1;
}

