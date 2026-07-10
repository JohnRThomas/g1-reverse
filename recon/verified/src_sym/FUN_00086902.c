/* Reconstructed FUN_00086902 @ 0x86902  (parity: 300/300 trials, PROVEN) */

extern int FUN_00075980(float x);
float FUN_00086902(float param_1,float param_2)
{
  int iVar1;
  iVar1 = FUN_00075980(param_1);
  if ((iVar1 == 0) ||
     ((iVar1 = FUN_00075980(param_2), iVar1 != 0) &&
      (param_1 == param_2 || (param_1 < param_2) != ((param_1 != param_1) || (param_2 != param_2))))) {
    param_1 = param_2;
  }
  return param_1;
}

