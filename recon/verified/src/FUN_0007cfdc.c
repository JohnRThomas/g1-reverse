/* Reconstructed FUN_0007cfdc @ 0x7cfdc  (parity: 300/300 trials, PROVEN) */

extern int FUN_00030178(unsigned int a, unsigned int b);
extern int FUN_0007cfac(void);

int FUN_0007cfdc(unsigned int param_1, unsigned int param_2)
{
  int iVar1;

  iVar1 = FUN_00030178(0x4704,param_1);
  if ((((iVar1 == 0) && (iVar1 = FUN_00030178(0x4708,param_2), iVar1 == 0)) &&
      (iVar1 = FUN_00030178(0x4710,0xc), iVar1 == 0)) &&
     (iVar1 = FUN_00030178(0x4714,1), iVar1 == 0)) {
    iVar1 = FUN_0007cfac();
    if (iVar1 != 0) {
      iVar1 = 1;
    }
    iVar1 = -iVar1;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}

