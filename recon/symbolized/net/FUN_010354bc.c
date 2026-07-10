#include "g1_net_symbols.h"
/* net-core FUN_010354bc @ 0x10354bc  (parity 300 trials PROVEN) */
extern void FUN_0103547c(int, unsigned char *, unsigned int, unsigned int, unsigned int, int, unsigned int, unsigned int);
extern void FUN_01036824(int);
extern void FUN_0103ad4a(int);
extern void FUN_0103ad56(unsigned char *);
extern unsigned int FUN_0103ada8(unsigned char *, int);

#define DAT_010355b4 0xfffff82du
#define DAT_010355b8 0xfffff829u

unsigned int FUN_010354bc(unsigned char *param_1, int param_2, unsigned int param_3,
                           unsigned int param_4, unsigned int param_5, int param_6,
                           unsigned int param_7)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  int iVar6;

  if (param_1 == (unsigned char *)0) {
    return DAT_010355b4;
  }
  if (param_2 == 0) {
    return DAT_010355b4;
  }
  if (param_6 == 0) {
    return DAT_010355b4;
  }
  iVar6 = param_2 + 0x58;
  uVar3 = param_4;
  FUN_0103ad4a(iVar6);
  if (param_4 == 0xffffffffu) {
    iVar1 = param_2 + 0x48;
    uVar2 = *(unsigned int *)(long)iVar1 & 1;
    if (uVar2 != 0) {
      uVar2 = 0;
      do {
        uVar2 = uVar2 + 1;
        uVar5 = DAT_010355b8;
        if (uVar2 == 0x80) goto LAB_0103559e;
      } while ((int)((*(unsigned int *)(long)(iVar1 + (int)(uVar2 >> 5) * 4) >> (uVar2 & 0x1f)) << 0x1f) < 0);
    }
    param_4 = uVar2 + 0x400;
    *(unsigned int *)(long)(iVar1 + (int)(uVar2 >> 5) * 4) =
        *(unsigned int *)(long)(iVar1 + (int)(uVar2 >> 5) * 4) | (1u << (uVar2 & 0x1f));
  } else if (0x3ff < param_4) {
    uVar2 = param_4 - 0x400;
    uVar5 = DAT_010355b4;
    if (uVar2 < 0x80) {
      uVar4 = *(unsigned int *)(long)(param_2 + 0x48 + (int)(uVar2 >> 5) * 4);
      uVar5 = DAT_010355b8;
      if (-1 < (int)((uVar4 >> (uVar2 & 0x1f)) << 0x1f)) {
        *(unsigned int *)(long)(param_2 + 0x48 + (int)(uVar2 >> 5) * 4) = (1u << (uVar2 & 0x1f)) | uVar4;
        goto LAB_01035524;
      }
    }
LAB_0103559e:
    FUN_01036824(iVar6);
    return uVar5;
  }
LAB_01035524:
  FUN_0103547c(param_2, param_1, param_3, param_4, param_5, param_6, param_7, uVar3);
  FUN_01036824(iVar6);
  uVar3 = (unsigned int)*param_1;
  if ((uVar3 != 0) && (uVar3 = (unsigned int)*(unsigned char *)(long)(param_2 + 0x90), uVar3 != 0)) {
    if (*(int *)(param_1 + 0x28) == -1) {
      uVar3 = FUN_0103ada8(param_1, 0);
      if (uVar3 != 0) {
        FUN_0103ad56(param_1);
      }
    } else {
      uVar3 = 0;
    }
  }
  return uVar3;
}

