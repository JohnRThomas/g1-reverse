/* net-core FUN_01032860 @ 0x1032860  (parity 300 trials PROVEN) */

extern unsigned int FUN_010218c0(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_01033c74(void);

void FUN_01032860(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  unsigned int uVar3;
  unsigned int iVar2;
  unsigned int *piVar1;

  uVar3 = (param_1 == 0) ? 0x40000u : 0x40004u;
  iVar2 = FUN_010218c0(0x0103cae8u, 0x2100065cu, param_3, param_4);
  piVar1 = (unsigned int *)0x21000698u;
  if (iVar2 == 0) {
    FUN_01033c74();
  } else {
    *(volatile unsigned int *)(*(volatile unsigned int *)0x21000698u + 0x548) = 0x81;
  }
  *(volatile unsigned int *)(*piVar1 + 0x200) = uVar3;
  return;
}

