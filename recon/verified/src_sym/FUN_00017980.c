/* Reconstructed FUN_00017980 @ 0x17980  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void assert_post_action(unsigned int a, unsigned int b);
typedef int (*ifn5)(unsigned int, void*, unsigned int, unsigned int, unsigned int);
int FUN_00017980(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
  int iVar1;
  ifn5 pcVar2;
  unsigned int uVar3;
  volatile unsigned int *puVar4;
  unsigned int local_14;
  unsigned int uStack_10;

  uVar3 = 1u << (param_1 & 0xff);
  local_14 = param_2;
  uStack_10 = param_3;
  if ((uVar3 & *(volatile unsigned int *)(*(volatile unsigned int *)(0x87b60UL + 4))) == 0) {
    printk(0x99cbd, 0x99de0, 0x99c53, 0x5f6);
    printk(0x99e1e, 0, 0, 0);
    assert_post_action(0x99c53, 0x5f6);
  }
  puVar4 = *(volatile unsigned int **)(0x87b60UL + 0x10);
  pcVar2 = *(ifn5 *)(*(volatile unsigned int *)(0x87b60UL + 8) + 4);
  iVar1 = (*pcVar2)(0x87b60UL, &local_14, param_3, (unsigned int)pcVar2, param_1);
  if (iVar1 == 0) {
    if (((local_14 ^ *puVar4) & uVar3) == 0) iVar1 = 0; else iVar1 = 1;
  }
  return iVar1;
}

