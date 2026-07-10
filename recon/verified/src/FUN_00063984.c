/* Reconstructed FUN_00063984 @ 0x63984  (parity: 300/300 trials, PROVEN) */

extern int FUN_00083e70(unsigned int a, int b, unsigned int c, unsigned int d, unsigned int e);
extern int FUN_00083dc8(unsigned int a, int b, int c, unsigned char d);

int FUN_00063984(int param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  volatile char *pcVar2;
  volatile unsigned int *puVar3;

  pcVar2 = *(volatile char **)(param_1 + 0x10);
  puVar3 = *(volatile unsigned int **)(param_1 + 4);
  if (*pcVar2 != 0) {
    return -0xc;
  }
  if (*param_2 == 0) {
    iVar1 = FUN_00083e70(*puVar3, param_2[1], param_3, 0, param_4);
    if (iVar1 < 0) {
      return iVar1;
    }
    if ((*(volatile unsigned char *)((char*)param_2 + 0xc) & 3) != 3) {
      unsigned char idx = *(volatile unsigned char *)((char*)param_2 + 0xc) & 3;
      iVar1 = FUN_00083dc8(*puVar3, 7, 5, *(volatile unsigned char *)(0xf66c1UL + idx));
      if (iVar1 < 0) {
        return iVar1;
      }
      *pcVar2 = 1;
      return 0;
    }
  }
  return -0x16;
}

