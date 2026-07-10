/* Reconstructed FUN_0005b754 @ 0x5b754  (parity: 300/300 trials, PROVEN) */

extern int FUN_0005a9f4();
extern int FUN_0005aa84(int,...);
extern int FUN_0005b680(int,...);
extern int FUN_0007e2ec(int,...);
extern int FUN_0007e2fa(int,...);
extern int FUN_00080d3e(int,...);
extern int FUN_0008270c(int,...);
extern int FUN_00082c0e();

int FUN_0005b754(int param_1, int *param_2)
{
  int iVar1;
  int uVar2;
  unsigned char local_28[2];
  unsigned short local_26;
  unsigned int *local_24;
  unsigned short local_20;
  int local_1c;
  unsigned short local_18;
  int *local_14;

  if (param_2 == 0) {
    FUN_0007e2fa(0x99cbd, 0xf4b3d, 0xf46b8, 0xae3);
    FUN_0007e2fa(0xf4a0a);
    uVar2 = 0xae3;
  } else {
    if (param_2[1] != 0 || param_2[0] != 0) {
      iVar1 = FUN_0008270c(0x200020d4);
      if (-1 < (iVar1 << 0x1d)) {
        return 0xfffffff5;
      }
      if (param_1 != 0 && *(char*)(param_1+0xd) != 7) {
        return 0xffffff80;
      }
      local_24 = (unsigned int*)param_2[1];
      iVar1 = FUN_0005a9f4();
      local_20 = (unsigned short)iVar1;
      if (param_2[0] == 0) {
        if (iVar1 != 0) goto LAB;
      } else {
        local_24 = 0;
        FUN_0005aa84(iVar1, 0xffff, param_2[0], 0, 1, 0x825fb, &local_24);
        if (local_24 != 0) {
          param_2[1] = (int)local_24;
LAB:
          local_28[0] = 0;
          local_26 = 0x2803;
          iVar1 = FUN_00080d3e(*local_24, local_28);
          if (iVar1 == 0) {
            if (-1 < (int)((unsigned int)(*(unsigned char*)(local_24[3]+6)) << 0x1b)) {
              return 0xffffffea;
            }
            local_20 = (unsigned short)FUN_00082c0e();
          }
          if (param_1 != 0) {
            uVar2 = FUN_0005b680(param_1, local_20, param_2);
            return uVar2;
          }
          local_1c = 0xffffff80;
          local_26 = 0x2902;
          local_18 = 1;
          local_28[0] = 0;
          local_14 = param_2;
          FUN_0005aa84(local_20, 0xffff, local_28, 0, 1, 0x5b891, &local_24);
          return local_1c;
        }
      }
      return 0xfffffffe;
    }
    FUN_0007e2fa(0x99cbd, 0xf4b44, 0xf46b8, 0xae4);
    FUN_0007e2fa(0xf4a0a);
    uVar2 = 0xae4;
  }
  FUN_0007e2ec(0xf46b8, uVar2);
  return 0;
}

