/* Reconstructed FUN_00084d8c @ 0x84d8c  (parity: 300/300 trials, PROVEN) */

extern unsigned int FUN_0007f012(unsigned long);

unsigned int FUN_00084d8c(unsigned int param_1, unsigned char *param_2, int param_3)
{
  (void)param_1;
  if (param_2 == 0 || param_3 == 0) return 0;
  unsigned int uVar1 = FUN_0007f012(param_1);
  unsigned char *pbVar4 = param_2;
  unsigned char *pbVar3;
  do {
    pbVar3 = pbVar4 + 1;
    if (*pbVar4 != uVar1) return 0;
    pbVar4 = pbVar3;
  } while (pbVar3 != param_2 + param_3);
  return 1;
}

