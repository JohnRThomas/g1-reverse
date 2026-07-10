/* Reconstructed FUN_00083896 @ 0x83896  (parity: 300/300 trials, PROVEN) */

extern int FUN_00054c64(void);
extern unsigned int FUN_00053e74(unsigned int, unsigned int);

unsigned int FUN_00083896(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  unsigned int uVar2;

  iVar1 = FUN_00054c64();
  if (iVar1 != 0) {
    uVar2 = FUN_00053e74(param_2,param_3);
    return uVar2;
  }
  return 0xfffffff5;
}

