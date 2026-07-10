/* Reconstructed FUN_000177c4 @ 0x177c4  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int, unsigned int, unsigned int, unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
typedef int (*fnptr)(int, unsigned int*, unsigned int, void*, int);

int FUN_000177c4(char *param_1, unsigned int param_2)
{
  unsigned int uVar3 = 1u << (param_2 & 0xff);
  unsigned int local_c = param_2;
  if ((uVar3 & **(unsigned int**)(param_1+4)) == 0) {
    printk(0x99cbd, 0x99de0, 0x99c53, 0x5d1);
    printk(0x99e1e, 0, 0, 0);
    assert_post_action(0x99c53, 0x5d1);
  }
  fnptr pcVar2 = *(fnptr*)(*(int*)(param_1+8)+4);
  int iVar1 = pcVar2((int)param_1, &local_c, **(unsigned int**)(param_1+4), (void*)pcVar2, (int)param_1);
  if (iVar1==0) {
    iVar1 = (uVar3 & local_c)!=0 ? 1:0;
  }
  return iVar1;
}

