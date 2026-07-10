/* named: FUN_00030c24 */
/* Reconstructed FUN_00030c24 @ 0x30c24  (parity: 300/300 trials, PROVEN) */

typedef int (*fnptr)(unsigned int, void *, int, int);

int FUN_00030c24(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int local_20;
  unsigned int uStack_1c;
  unsigned char local_18;
  unsigned int local_14;
  unsigned int uStack_10;
  unsigned char local_c;
  unsigned int base;
  int field;
  fnptr fp;
  local_18 = 0;
  local_c = 7;
  local_20 = param_1;
  uStack_1c = param_2;
  local_14 = param_3;
  uStack_10 = param_4;
  base = *(volatile unsigned int *)0x20002418UL;
  field = *(int *)(base + 8);
  fp = *(fnptr *)(field + 8);
  iVar1 = fp(base, &local_20, 2, 0x12);
  if (iVar1 != 0) iVar1 = 1;
  return -iVar1;
}

