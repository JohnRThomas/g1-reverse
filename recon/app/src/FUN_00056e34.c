/* Reconstructed FUN_00056e34 @ 0x56e34  (parity: 300/300 trials, PROVEN) */

extern int FUN_000562a4(unsigned int, int, unsigned int, unsigned int, unsigned int);

void FUN_00056e34(unsigned char param_1, unsigned int *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  iVar1 = FUN_000562a4(0x20006138, 1, param_3, param_4, param_4);
  if (iVar1 != 0) {
    *(unsigned char *)(iVar1 + 8) = param_1;
    *(unsigned int *)(iVar1 + 0x90) = *param_2;
    *(unsigned short *)(iVar1 + 0x94) = *(unsigned short *)(param_2 + 1);
    *(unsigned char *)(iVar1 + 0x96) = *((unsigned char *)param_2 + 6);
    *(unsigned char *)(iVar1 + 9) = 2;
    *(unsigned char *)(iVar1 + 10) = 2;
    *(unsigned char *)(iVar1 + 2) = 1;
    *(unsigned int *)(iVar1 + 0xa8) = 0x00280018;
  }
}

