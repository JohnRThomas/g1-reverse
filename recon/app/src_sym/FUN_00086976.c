/* Reconstructed FUN_00086976 @ 0x86976  (parity: 300/300 trials, PROVEN) */

extern int FUN_000869f2(void);
extern float FUN_00075a0c(float, int);
extern int *thunk_FUN_00071678(void);

float FUN_00086976(float param_1, unsigned int param_2)
{
  int iVar1;
  int *puVar2;

  iVar1 = FUN_000869f2();
  if ((iVar1 != 0) && (param_1 != 0.0f)) {
    param_1 = FUN_00075a0c(param_1, param_2);
    iVar1 = FUN_000869f2();
    if ((iVar1 == 0) || (param_1 == 0.0f)) {
      puVar2 = thunk_FUN_00071678();
      *puVar2 = 0x22;
    }
  }
  return param_1;
}

