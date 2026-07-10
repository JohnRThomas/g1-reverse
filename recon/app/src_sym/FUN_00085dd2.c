/* Reconstructed FUN_00085dd2 @ 0x85dd2  (parity: 300/300 trials, PROVEN) */

extern int FUN_00085d82(void);
extern void FUN_00085d70(unsigned int *a0, int a1);

int FUN_00085dd2(unsigned int *param_1)
{
  int iVar1;
  iVar1 = FUN_00085d82();
  if (iVar1 != 0) {
    unsigned char *p = (unsigned char *)*param_1;
    if (*p == 0xff) {
      *param_1 = (unsigned int)(p + 1);
      return iVar1;
    }
    FUN_00085d70(param_1, 10);
  }
  return 0;
}

