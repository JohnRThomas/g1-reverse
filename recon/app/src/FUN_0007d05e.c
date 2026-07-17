/* Reconstructed FUN_0007d05e @ 0x7d05e  (parity: 300/300 trials, PROVEN) */

extern int FUN_00030178(unsigned int a, ...);
extern int FUN_000302f8(unsigned int a, unsigned int b);
extern int FUN_0007cfac(void);

int FUN_0007d05e(unsigned int param_1)
{
  int iVar1;

  iVar1 = FUN_00030178(0x4704);
  if ((((iVar1 == 0) && (iVar1 = FUN_00030178(0x4710,3), iVar1 == 0)) &&
      (iVar1 = FUN_00030178(0x4714,1), iVar1 == 0)) && (iVar1 = FUN_0007cfac(), iVar1 == 0)) {
    iVar1 = FUN_000302f8(0x470c,param_1);
    if (iVar1 != 0) {
      iVar1 = 1;
    }
    iVar1 = -iVar1;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}
