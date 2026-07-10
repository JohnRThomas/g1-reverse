#include "g1_net_symbols.h"
/* net-core FUN_0103566c @ 0x103566c  (parity 300 trials PROVEN) */
extern void FUN_010353ec(unsigned int, unsigned short, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void FUN_01039bbe(unsigned int, unsigned int, unsigned int);
extern int *FUN_0103ac50(unsigned int, int, int *);
extern void FUN_0103acca(unsigned int);
extern int FUN_0103ae10(int, int, int, unsigned int);
extern void FUN_0103aec6(int);
extern void thunk_FUN_01036824(int);

typedef int (*fnptr)(int, void *, short, int, unsigned int);

#define DAT_01035764 ((uintptr_t)&rodata_103e889) /*=0x103e889*/
#define DAT_01035768 "acking error (context area might be not valid)" /*=0x103d2a7*/

void FUN_0103566c(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int bVar6;
  unsigned int uStack_20;
  unsigned int local_1c;

  iVar4 = *(int *)(long)(*param_1 + 0x24);
  iVar5 = iVar4 + 0x58;
  uStack_20 = param_3;
  local_1c = param_4;
  FUN_0103aec6(iVar5);
  if (*(int *)(long)(*(int *)(long)(iVar4 + 0xa0) + 0x18) != 1) {
    thunk_FUN_01036824(iVar5);
    return;
  }
  piVar1 = FUN_0103ac50(*(unsigned int *)(long)(iVar4 + 0xa4),
                         (int)(long)&uStack_20 + 2, (int *)&local_1c);
  thunk_FUN_01036824(iVar5);
  if (piVar1 == (int *)0) {
    return;
  }
  do {
    piVar1[2] = (int)(uStack_20 >> 0x10);
    FUN_0103aec6(iVar5);
    iVar2 = FUN_0103ae10(iVar4, 0, piVar1[1], 0xffffffffu);
    thunk_FUN_01036824(iVar5);
    if (iVar2 != 0) {
      iVar3 = *(int *)(long)(iVar2 + 0x28) + 1;
      bVar6 = iVar3 == 0;
      if (bVar6) {
        iVar3 = *piVar1;
      }
      if (bVar6) {
        *(int *)(long)(iVar2 + 0x28) = iVar3;
      }
      {
        fnptr fp = *(fnptr *)(long)(iVar2 + 0x2c);
        iVar2 = fp(iVar2, piVar1 + 4, (short)piVar1[3], *piVar1,
                    *(unsigned int *)(long)(iVar2 + 0x3c));
      }
      if (iVar2 < 0) {
        FUN_01039bbe(DAT_01035768, DAT_01035764, 0x245);
        FUN_01039bb0(DAT_01035764, 0x245);
        __builtin_unreachable();
      }
    }
    FUN_0103aec6(iVar5);
    if (-1 < piVar1[2]) {
      if (*(int *)(long)(*(int *)(long)(iVar4 + 0xa0) + 0x18) != 1) {
LAB_01035728:
        FUN_0103acca(*(unsigned int *)(long)(iVar4 + 0xa4));
        thunk_FUN_01036824(iVar5);
        return;
      }
      FUN_010353ec(*(unsigned int *)(long)(iVar4 + 0xa4), (unsigned short)(uStack_20 >> 16), local_1c);
    }
    if ((*(int *)(long)(*(int *)(long)(iVar4 + 0xa0) + 0x18) != 1) ||
        (piVar1 = FUN_0103ac50(*(unsigned int *)(long)(iVar4 + 0xa4),
                                (int)(long)&uStack_20 + 2, (int *)&local_1c),
         piVar1 == (int *)0)) {
      goto LAB_01035728;
    }
    thunk_FUN_01036824(iVar5);
  } while (1);
}

