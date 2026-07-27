/* Reconstructed FUN_00085da2 @ 0x85da2  (parity: 300/300 trials, PROVEN) */

extern int FUN_00085d82(unsigned long);
extern void FUN_00085d70(int *a, int b, int c, unsigned char d, int e);
int FUN_00085da2(int **param_1, unsigned int param_2, int param_3, int param_4)
{
  int iVar1;
  iVar1 = FUN_00085d82(param_1);
  if (iVar1 != 0) {
    unsigned char *p = (unsigned char *)*param_1;
    if (param_2 == (unsigned int)(*(volatile unsigned char *)p >> 5)) {
      return iVar1;
    }
    FUN_00085d70((int *)param_1, 10, param_3, *(volatile unsigned char *)p, param_4);
  }
  return 0;
}

