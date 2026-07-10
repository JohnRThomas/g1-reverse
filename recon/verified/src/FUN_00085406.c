/* Reconstructed FUN_00085406 @ 0x85406  (parity: 300/300 trials, PROVEN) */

extern int FUN_00068134(char *a, char **b, int c, char d, char *e);

int FUN_00085406(char *param_1, char *param_2, int param_3)
{
  int iVar1;
  char *local_14;
  int iStack_10;

  if (param_1==0 || *param_1==0 || param_2==0 || *param_2==0 || param_3==0) {
    return -0x16;
  }
  local_14 = param_2;
  iStack_10 = param_3;
  iVar1 = FUN_00068134(param_1, &local_14, param_3, *param_2, param_1);
  if (iVar1 == 0) {
    void *fn = *(void**)(local_14+8);
    if (fn != 0) {
      return ((int(*)(char*,char*,int))fn)(local_14, param_2, param_3);
    }
    return -0x13;
  }
  return iVar1;
}

