/* named: ldexpf */
/* Reconstructed ldexpf @ 0x86976  (parity: 300/300 trials, PROVEN) */

extern int isfinitef(void);
extern float scalbnf(float a, unsigned int b);
extern int* thunk_FUN_00071678(void);

float ldexpf(float param_1, unsigned int param_2)
{
  int iVar1;
  int *puVar2;

  iVar1 = isfinitef();
  if ((iVar1 != 0) && (param_1 != 0.0f)) {
    param_1 = scalbnf(param_1, param_2);
    iVar1 = isfinitef();
    if ((iVar1 == 0) || (param_1 == 0.0f)) {
      puVar2 = thunk_FUN_00071678();
      *puVar2 = 0x22;
    }
  }
  return param_1;
}

