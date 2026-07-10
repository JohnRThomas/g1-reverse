/* Reconstructed FUN_0007d02a @ 0x7d02a  (parity: 300/300 trials, PROVEN) */

extern int FUN_00030288(unsigned int);
extern int FUN_0007cfdc(unsigned int, unsigned int);
extern int FUN_00030178(unsigned int, unsigned int);

int FUN_0007d02a(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  iVar1 = FUN_00030288(param_3);
  if (iVar1 == 0 && (iVar1 = FUN_0007cfdc(param_1, param_2)) == 0) {
    iVar1 = FUN_00030178(0x4820, 4);
    if (iVar1 != 0) iVar1 = 1;
    iVar1 = -iVar1;
  } else {
    iVar1 = -1;
  }
  return iVar1;
}

