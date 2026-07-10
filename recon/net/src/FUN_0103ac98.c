/* net-core FUN_0103ac98 @ 0x103ac98  (parity 300 trials PROVEN) */

void FUN_0103ac98(int *param_1)
{
  int iVar1 = *(int*)(*param_1 + 0x18);
  if ((*(int*)(*param_1 + 0x10) << 2) < 0) {
    if (iVar1 == 1) {
      *(short*)(param_1[8] + param_1[5]*8 + 4) =
          ((short)param_1[0xc] - 1) - *(short*)((char*)param_1 + 10);
    }
  } else if (iVar1 == 1) {
    *(unsigned short*)param_1[8] = *(unsigned short*)param_1[8] | 1;
  }
}

