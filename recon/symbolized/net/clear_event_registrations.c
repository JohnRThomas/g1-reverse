#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01038654 @ 0x01038654
 * public-name: clear_event_registrations
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   clear_event_registrations                <= FUN_01038654 @ 0x01038654
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eb7f                           @ 0x0103eb7f
 */
/* net-core FUN_01038654 @ 0x1038654  (parity 300 trials PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_cmsis_shim.h"

extern int FUN_0103610c(unsigned int);
extern int FUN_01036128(unsigned int);
extern void FUN_01036144(unsigned int);
extern void assert_post_action(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);

#define DAT_01038754 0x21004b78u
#define PTR_DAT_01038758 ((unsigned long)&rodata_103eb7f) /*=0x103eb7f*/
#define PTR_s_acking_error__context_area_might_0103875c ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define PTR_s_______HARD_FAULT_______01038760 ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/

void clear_event_registrations(int param_1, int param_2, unsigned int param_3)
{
  int bVar1;
  unsigned int uVar2;
  int iVar3;
  unsigned int puVar4;
  unsigned int uVar5;
  int *piVar6;
  int iVar7;

  uVar5 = DAT_01038754;
  iVar3 = param_2 * 0x14 + param_1;
  do {
    if (param_2 == 0) {
      return;
    }
    *(unsigned int *)(long)(iVar3 + -0xc) = 0;
    switch (*(unsigned char *)(long)(iVar3 + -7) & 0x3f) {
    case 0:
      goto switchD_01038680_caseD_0;
    case 1:
      if (*(int *)(long)(iVar3 + -4) == 0) {
        assert_print(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xbe);
        uVar5 = 0xbe;
        puVar4 = PTR_DAT_01038758;
        goto LAB_010386a2;
      }
      break;
    case 2:
      if (*(int *)(long)(iVar3 + -4) == 0) {
        assert_print(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xb6);
        uVar5 = 0xb6;
        puVar4 = PTR_DAT_01038758;
        goto LAB_010386a2;
      }
      break;
    default:
      assert_print(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xcf);
      uVar5 = 0xcf;
      puVar4 = PTR_DAT_01038758;
      goto LAB_010386a2;
    case 4:
      if (*(int *)(long)(iVar3 + -4) == 0) {
        assert_print(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xba);
        uVar5 = 0xba;
        puVar4 = PTR_DAT_01038758;
        goto LAB_010386a2;
      }
      break;
    case 8:
      if (*(int *)(long)(iVar3 + -4) == 0) {
        assert_print(PTR_s_acking_error__context_area_might_0103875c, PTR_DAT_01038758, 0xc2);
        uVar5 = 0xc2;
        puVar4 = PTR_DAT_01038758;
        goto LAB_010386a2;
      }
    }
    iVar7 = *(int *)(long)(iVar3 + -0x14);
    if (iVar7 != 0) {
      piVar6 = *(int **)(long)(iVar3 + -0x10);
      *piVar6 = iVar7;
      *(int **)(long)(iVar7 + 4) = piVar6;
      *(unsigned int *)(long)(iVar3 + -0x14) = 0;
      *(unsigned int *)(long)(iVar3 + -0x10) = 0;
    }
switchD_01038680_caseD_0:
    iVar7 = FUN_01036128(uVar5);
    if (iVar7 == 0) {
      assert_print(PTR_s_acking_error__context_area_might_0103875c,
                   PTR_s_______HARD_FAULT_______01038760, 0xf0);
      uVar5 = 0xf0;
      puVar4 = PTR_s_______HARD_FAULT_______01038760;
LAB_010386a2:
      assert_post_action(puVar4, uVar5);
      return;
    }
    bVar1 = isCurrentModePrivileged();
    if (bVar1) {
      setBasePriority((int)param_3);
    }
    InstructionSynchronizationBarrier(0xf);
    param_3 = 0;
    bVar1 = isCurrentModePrivileged();
    if (bVar1) {
      param_3 = (unsigned int)getBasePriority();
    }
    bVar1 = isCurrentModePrivileged();
    if (bVar1) {
      uVar2 = (unsigned int)getBasePriority();
      if (uVar2 == 0 || 0x40 < uVar2) {
        setBasePriority(0x40);
      }
    }
    InstructionSynchronizationBarrier(0xf);
    iVar7 = FUN_0103610c(uVar5);
    param_2 = param_2 - 1;
    if (iVar7 == 0) {
      assert_print(PTR_s_acking_error__context_area_might_0103875c,
                   PTR_s_______HARD_FAULT_______01038760, 0x72);
      uVar5 = 0x72;
      puVar4 = PTR_s_______HARD_FAULT_______01038760;
      goto LAB_010386a2;
    }
    FUN_01036144(uVar5);
    iVar3 -= 0x14;
  } while (1);
}
