#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103566c @ 0x0103566c
 * public-name: FUN_0103566c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e889                           @ 0x0103e889
 */
/* net-core FUN_0103566c @ 0x103566c  (parity 300 trials PROVEN) */
extern void FUN_010353ec(unsigned int, unsigned short, unsigned int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
#include <stdint.h>

extern int *FUN_0103ac50(unsigned int, uint16_t *, uint32_t *);
extern void FUN_0103acca(unsigned int);
extern int FUN_0103ae10(int, int, int, unsigned int);
extern void FUN_0103aec6(int);
extern void thunk_FUN_01036824(int);

typedef int (*fnptr)(int, void *, unsigned short, int, unsigned int);

#define DAT_01035764 ((unsigned long)&rodata_103e889) /*=0x103e889*/
#define DAT_01035768 ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/

void FUN_0103566c(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int *piVar1;
  int iVar2;
  int iVar4;
  int iVar5;
  int bVar6;
  union {
    uint32_t word;
    uint16_t half[2];
  } selector;
  uint32_t local_1c;

  iVar4 = *(int *)(uintptr_t)(*param_1 + 0x24);
  iVar5 = iVar4 + 0x58;
  selector.word = param_3;
  local_1c = param_4;
  FUN_0103aec6(iVar5);
  if (*(int *)(uintptr_t)(*(int *)(uintptr_t)(iVar4 + 0xa0) + 0x18) != 1) {
    thunk_FUN_01036824(iVar5);
    return;
  }
  piVar1 = FUN_0103ac50(*(unsigned int *)(uintptr_t)(iVar4 + 0xa4),
                         &selector.half[1], &local_1c);
  thunk_FUN_01036824(iVar5);
  if (piVar1 == (int *)0) {
    return;
  }
  do {
    piVar1[2] = (int)selector.half[1];
    FUN_0103aec6(iVar5);
    iVar2 = FUN_0103ae10(iVar4, 0, piVar1[1], 0xffffffffu);
    thunk_FUN_01036824(iVar5);
    if (iVar2 != 0) {
      uint32_t next_state =
          (uint32_t)*(int *)(uintptr_t)(iVar2 + 0x28) + 1u;
      bVar6 = next_state == 0u;
      if (bVar6) {
        next_state = (uint32_t)*piVar1;
      }
      if (bVar6) {
        *(uint32_t *)(uintptr_t)(iVar2 + 0x28) = next_state;
      }
      {
        fnptr fp = *(fnptr *)(uintptr_t)(iVar2 + 0x2c);
        iVar2 = fp(iVar2, piVar1 + 4, (unsigned short)piVar1[3], *piVar1,
                    *(unsigned int *)(uintptr_t)(iVar2 + 0x3c));
      }
      if (iVar2 < 0) {
        assert_print(DAT_01035768, DAT_01035764, 0x245);
        FUN_01039bb0(DAT_01035764, 0x245);
        __builtin_unreachable();
      }
    }
    FUN_0103aec6(iVar5);
    if (-1 < piVar1[2]) {
      if (*(int *)(uintptr_t)(*(int *)(uintptr_t)(iVar4 + 0xa0) + 0x18) != 1) {
LAB_01035728:
        FUN_0103acca(*(unsigned int *)(uintptr_t)(iVar4 + 0xa4));
        thunk_FUN_01036824(iVar5);
        return;
      }
      FUN_010353ec(*(unsigned int *)(uintptr_t)(iVar4 + 0xa4), selector.half[1], local_1c);
    }
    if ((*(int *)(uintptr_t)(*(int *)(uintptr_t)(iVar4 + 0xa0) + 0x18) != 1) ||
        (piVar1 = FUN_0103ac50(*(unsigned int *)(uintptr_t)(iVar4 + 0xa4),
                                &selector.half[1], &local_1c),
         piVar1 == (int *)0)) {
      goto LAB_01035728;
    }
    thunk_FUN_01036824(iVar5);
  } while (1);
}
