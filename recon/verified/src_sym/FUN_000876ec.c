/* Reconstructed FUN_000876ec @ 0x876ec  (parity: 300/300 trials, PROVEN) */

extern void FUN_00076d8c(unsigned int a, int b);
extern int FUN_00076e20(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void memcpy(int a, int b, unsigned int c);
extern unsigned int FUN_00087996(void);
int FUN_000876ec(unsigned int param_1,int param_2,unsigned int param_3,unsigned int param_4)
{
  int iVar1;
  unsigned int uVar2;

  if (param_2 == 0) {
    iVar1 = FUN_00076e20(param_1,param_3,param_3,param_4);
    return iVar1;
  }
  if (param_3 == 0) {
    FUN_00076d8c(param_1, param_2);
  } else {
    uVar2 = FUN_00087996();
    if (param_3 <= uVar2) {
      return param_2;
    }
    iVar1 = FUN_00076e20(param_1,param_3,param_3,param_4);
    if (iVar1 != 0) {
      memcpy(iVar1,param_2,param_3);
      FUN_00076d8c(param_1,param_2);
      return iVar1;
    }
  }
  return 0;
}

