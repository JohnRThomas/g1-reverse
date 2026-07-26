#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036660 @ 0x01036660
 * public-name: FUN_01036660
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   z_handle_obj_poll_events                 <= FUN_0103b4f6 @ 0x0103b4f6
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 */
/* net-core FUN_01036660 @ 0x1036660  (parity 300 trials PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_cmsis_shim.h"

extern int FUN_0103610c(unsigned int*);
extern int FUN_01036128(unsigned int*);
extern void FUN_01036144(unsigned int*);
extern void FUN_0103705c(void);
extern void FUN_01037130(unsigned int*, unsigned int);
extern int FUN_010379d4(unsigned int*);
extern unsigned int *FUN_010389f8(int, int);
extern void assert_post_action(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern void z_handle_obj_poll_events(unsigned int*, int);

#define DAT_0103676c ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/
#define DAT_01036770 ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/

unsigned int FUN_01036660(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3, int param_4, char param_5)
{
  int bVar1;
  int iVar2;
  unsigned int *puVar3;
  unsigned int uVar4;
  unsigned int *puVar5;
  unsigned int uVar6;

  puVar5 = param_1 + 2;
  uVar6 = 0;
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar6 = getBasePriority();
  }
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar4 = getBasePriority();
    if (uVar4 == 0 || 0x40 < uVar4) {
      setBasePriority(0x40);
    }
  }
  InstructionSynchronizationBarrier(0xf);
  iVar2 = FUN_0103610c(puVar5);
  if (iVar2 == 0) {
    assert_print(DAT_01036770, DAT_0103676c, 0x72);
    uVar6 = 0x72;
    assert_post_action(DAT_0103676c, uVar6);
    __builtin_unreachable();
  }
  FUN_01036144(puVar5);
  if (param_5 != 0) {
    param_2 = (unsigned int *)param_1[1];
  }
  iVar2 = FUN_010379d4(param_1 + 3);
  if (iVar2 != 0) {
    *(unsigned int **)(iVar2 + 0x14) = param_3;
    *(volatile unsigned int *)(iVar2 + 0x90) = 0;
    FUN_0103705c();
    goto LAB_010366c4;
  }
  if (param_4 == 0) {
    *param_3 = 0;
  } else {
    puVar3 = FUN_010389f8(0, 8);
    if (puVar3 == (unsigned int *)0) {
      iVar2 = FUN_01036128(puVar5);
      if (iVar2 != 0) {
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority((int)uVar6);
        }
        InstructionSynchronizationBarrier(0xf);
        return 0xfffffff4;
      }
      assert_print(DAT_01036770, DAT_0103676c, 0xf0);
      uVar6 = 0xf0;
      assert_post_action(DAT_0103676c, uVar6);
      __builtin_unreachable();
    }
    puVar3[1] = (unsigned int)param_3;
    *puVar3 = 1;
    param_3 = puVar3;
  }
  uVar4 = *param_3 & 3;
  if (param_2 == (unsigned int *)0) {
    *param_3 = *param_1 | uVar4;
    *param_1 = (unsigned int)param_3;
    if (param_1[1] == 0) {
      param_1[1] = (unsigned int)param_3;
    }
  } else if (*param_2 < 4) {
    *param_3 = uVar4;
    puVar3 = (unsigned int *)param_1[1];
    if (puVar3 != (unsigned int *)0) {
      *puVar3 = (*puVar3 & 3) | (unsigned int)param_3;
      param_1[1] = (unsigned int)param_3;
    } else {
      *param_1 = (unsigned int)param_3;
      param_1[1] = (unsigned int)param_3;
    }
  } else {
    *param_3 = (*param_2 & 0xfffffffc) | uVar4;
    *param_2 = (unsigned int)param_3 | (*param_2 & 3);
  }
  z_handle_obj_poll_events(param_1 + 5, 4);
LAB_010366c4:
  FUN_01037130(puVar5, uVar6);
  return 0;
}
