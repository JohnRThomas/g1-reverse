/* net-core FUN_01039bd8 @ 0x1039bd8  (parity 300 trials PROVEN) */

int FUN_01039bd8(unsigned int *param_1, int *param_2)
{
  int iVar1, iVar3;
  unsigned int uVar2;

  if ((param_1[4] & 8) == 0) {
    uVar2 = *param_1;
    if (uVar2 < param_1[3]) {
      iVar1 = 0;
      iVar3 = (int)param_1[3] - (int)uVar2;
    } else {
      iVar1 = 1;
      iVar3 = (int)param_1[9] - (int)uVar2;
    }
  } else {
    iVar1 = 0;
    iVar3 = 0;
  }
  *param_2 = iVar3;
  return iVar1;
}

