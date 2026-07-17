#include "g1_net_symbols.h"
/* net-core FUN_0101bf30 @ 0x101bf30  (parity 300 trials PROVEN) */
#define C_0101bfc0 ((unsigned long)&g_net_link_ctx_b) /*=0x21001124*/
#define P_0101bfc4 ((unsigned long)&g_net_link_ctx_b_close_cb) /*=0x210004d0*/

extern void FUN_0101f934(int, int);
extern unsigned int FUN_0100f0fc(int);
extern int FUN_0100f1f8(int);
extern void FUN_0100f300(unsigned short, void *, void *);
extern void FUN_0101bdd4(int, int);
extern unsigned int FUN_01023e88(void);
extern int FUN_01023ea8(unsigned int, unsigned int);

typedef void (*fp_t)(int);

int FUN_0101bf30(void)
{
  unsigned int uVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  int iVar4;
  unsigned char cVar5;
  unsigned short *puVar6;
  unsigned char cVar7;
  fp_t pcVar8;
  int iVar9;

  iVar4 = C_0101bfc0;
  iVar9 = *(int *)(C_0101bfc0 + 4);
  cVar5 = *(unsigned char *)(iVar9 + 0x31a);
  if (cVar5 == 0) {
    cVar5 = *(unsigned char *)(iVar9 + 0x6e);
  }
  cVar7 = *(unsigned char *)(iVar9 + 0x31b);
  if (cVar7 == 0) {
    cVar7 = *(unsigned char *)(iVar9 + 0x6f);
  }
  *(volatile unsigned char *)(iVar9 + 0x6e) = cVar5;
  *(volatile unsigned char *)(iVar9 + 0x6f) = cVar7;
  pcVar8 = (fp_t)(*(volatile int *)P_0101bfc4);
  *(volatile unsigned char *)(iVar9 + 0x70) = 0xff;
  if (pcVar8 != (fp_t)0) {
    pcVar8(*(int *)(iVar4 + 4));
  }
  FUN_0101f934(C_0101bfc0, 0);
  uVar1 = FUN_0100f0fc(*(int *)(iVar4 + 4) + 0x30);
  iVar9 = FUN_0100f1f8(*(int *)(iVar4 + 4));
  if (iVar9 != 0) {
    puVar6 = *(unsigned short **)(iVar4 + 4);
    FUN_0100f300(*puVar6, puVar6 + 0x18, puVar6 + 0xe7);
  }
  FUN_0101bdd4(*(int *)(iVar4 + 4), 4);
  uVar2 = FUN_0100f0fc(*(int *)(iVar4 + 4) + 0x30);
  if (uVar2 <= uVar1) {
    return 1;
  }
  uVar3 = FUN_01023e88();
  uVar2 = uVar2 - uVar1;
  if (uVar2 < 0x76) {
    uVar2 = 0x76;
  }
  iVar4 = FUN_01023ea8(uVar2, uVar3);
  return iVar4 == 0;
}
