#include "g1_net_symbols.h"
/* net-core FUN_01029e64 @ 0x1029e64  (parity 3 trials PROVEN) */
typedef int (*fp_t)(int, int);

extern void FUN_01021a1c(void);
extern unsigned long long FUN_01022f0c(int a);
extern int FUN_010231c8(int a, void *b);
extern int FUN_01023ac4(void);
extern unsigned long long FUN_010256dc(int a, int b);
extern void FUN_01029d34(int a, void *b);
extern void FUN_01029d68(void);
extern int FUN_01029d76(void *a, int b);

void FUN_01029e64(char *param_1, int param_2)
{
  char *p = param_1;
  int cVar1;
  int uVar4;
  int iVar3;
  fp_t pcVar6;
  char *pcVar2;
  unsigned long long rv;

  if (p == 0) { uVar4 = 0x196; goto ERR; }

BODY:
  cVar1 = *(unsigned char *)(p + 0x28);
  switch (param_2) {
  case 0:
    if (1u < (unsigned int)((unsigned char)p[0x26] - 3)) { uVar4 = 0x1a1; goto ERR; }
    goto LAB_e98;
  case 1:
    if (1u < (unsigned int)((unsigned char)p[0x26] - 3)) { uVar4 = 0x1a5; goto ERR; }
    p[0x26] = 5;
    p[0x29] = 0;
    if (p[0x24] != 0) { FUN_01021a1c(); return; }
    FUN_01029d68();
    if (*(unsigned char *)p == 1) {
      unsigned long long uVar7 = FUN_01022f0c(*(unsigned char *)(p + 0x27));
      *(unsigned int *)(p + 0x18) = (unsigned int)uVar7;
      *(unsigned int *)(p + 0x1c) = (unsigned int)(uVar7 >> 32);
    } else {
      *(unsigned int *)(p + 0x18) = *(unsigned int *)(p + 0x10);
      *(unsigned int *)(p + 0x1c) = *(unsigned int *)(p + 0x14);
    }
    pcVar6 = *(fp_t *)(p + 0x20);
    uVar4 = 0;
    goto LAB_ee8;
  case 2:
  case 3:
    if (1u < (unsigned int)((unsigned char)p[0x26] - 3)) { uVar4 = 0x1c3; goto ERR; }
    if (p[0x24] == 0) {
      if ((unsigned char)p[0x26] == 4) p[0x26] = 2; else p[0x26] = 1;
      pcVar6 = *(fp_t *)(p + 0x20);
      if (param_2 == 2) {
        pcVar2 = (char *)pcVar6(cVar1, 5);
        if (pcVar2 == 0) return;
        if (*pcVar2 == 0) return;
        uVar4 = 0x1d8; goto ERR;
      }
      pcVar2 = (char *)pcVar6(cVar1, 6);
      if (pcVar2 != 0 && *pcVar2 != 0) { uVar4 = 0x1dd; goto ERR; }
    } else {
      FUN_01029d34(cVar1, p);
    }
    goto LAB_f3a;
  case 4:
    if ((unsigned char)p[0x26] != 5) { uVar4 = 0x1e4; goto ERR; }
    pcVar6 = *(fp_t *)(p + 0x20);
    uVar4 = 2;
    goto LAB_ee8;
  case 5:
    if ((unsigned char)p[0x26] != 5) { uVar4 = 0x1ea; goto ERR; }
    pcVar6 = *(fp_t *)(p + 0x20);
    uVar4 = 1;
  LAB_ee8:
    while (1) {
      uVar4 = pcVar6(cVar1, uVar4);
      iVar3 = FUN_01029d76(p, uVar4);
      if (iVar3 == 2) break;
      if (iVar3 == 0) { pcVar6 = *(fp_t *)(p + 0x20); uVar4 = 3; }
      else if (iVar3 == 1) { pcVar6 = *(fp_t *)(p + 0x20); uVar4 = 4; }
      else { uVar4 = 0x22a; goto ERR; }
    }
  LAB_f3a:
    if (param_2 == 0) {
    LAB_e98:
      iVar3 = FUN_01023ac4();
      if (iVar3 != 0) { uVar4 = 0x233; goto ERR; }
    }
    return;
  case 6:
    if ((unsigned char)p[0x26] == 5) { FUN_01021a1c(); return; }
    uVar4 = 0x1f0; goto ERR;
  case 7:
    if (((unsigned char)p[0x26] == 5) ||
        (p[0x25] != 0 && (unsigned char)p[0x26] == 3)) {
      if (p[0x24] != 0) { FUN_01029d34(cVar1, p); return; }
      if (p[0x29] == 0) {
        if (p[0x25] == 0) {
          p[0x26] = 2;
          pcVar2 = (char *)(*(fp_t *)(p + 0x20))(cVar1, 7);
          if (pcVar2 == 0) return;
          if (*pcVar2 == 0) return;
          uVar4 = 0x214; goto ERR;
        } else {
          p[0x25] = 0;
          iVar3 = FUN_010231c8(*(unsigned char *)(p + 0x27), p);
          if (iVar3 != 0) return;
          uVar4 = 0x20d; goto ERR;
        }
      } else {
        p[0x29] = 0;
        p[0x26] = 2;
        pcVar2 = (char *)(*(fp_t *)(p + 0x20))(cVar1, 8);
        if (pcVar2 == 0) return;
        if (*pcVar2 == 0) return;
        uVar4 = 0x208; goto ERR;
      }
    } else {
      uVar4 = 0x1fc; goto ERR;
    }
  case 8:
    if ((unsigned char)p[0x26] == 5) {
      uVar4 = (*(fp_t *)(p + 0x20))(cVar1, 10);
      FUN_01029d76(p, uVar4);
      uVar4 = 0x1f8; goto ERR;
    }
    uVar4 = 0x1f5; goto ERR;
  default:
    uVar4 = 0x219; goto ERR;
  }

ERR:
  rv = FUN_010256dc(0x6a, uVar4);
  p = (char *)(unsigned int)rv;
  param_2 = (int)(unsigned int)(rv >> 32);
  goto BODY;
}
