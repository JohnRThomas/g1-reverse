/* Reconstructed FUN_00017768 @ 0x17768  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(unsigned int a, unsigned int b);
typedef void (*jfn847)(void);
void FUN_00017768(int param_1, unsigned int param_2, unsigned int param_3)
{
  unsigned int uVar1;
  jfn847 UNRECOVERED_JUMPTABLE;

  uVar1 = 1u << (param_2 & 0xff);
  if ((uVar1 & **(volatile unsigned int **)(param_1 + 4)) == 0) {
    FUN_0007e2fa(0x99cbd, 0x99de0, 0x99c53, 0x64f);
    FUN_0007e2fa(0x99e1e, 0, 0, 0);
    FUN_0007e2ec(0x99c53, 0x64f);
  }
  if ((uVar1 & **(volatile unsigned int **)(param_1 + 0x10)) != 0) {
    param_3 = param_3 ^ 1;
  }
  if (param_3 == 0) {
    UNRECOVERED_JUMPTABLE = *(jfn847 *)(*(int *)(param_1 + 8) + 0x10);
  } else {
    UNRECOVERED_JUMPTABLE = *(jfn847 *)(*(int *)(param_1 + 8) + 0xc);
  }
  (*UNRECOVERED_JUMPTABLE)();
}

