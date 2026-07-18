#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00072674 @ 0x00072674
 * public-name: FUN_00072674
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_ready_thread_locked                    <= FUN_000738d4 @ 0x000738d4
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   z_unpend_first_thread                    <= FUN_000744a4 @ 0x000744a4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_handle_obj_poll_events                 <= FUN_0008688e @ 0x0008688e
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 */
/* Reconstructed FUN_00072674 @ 0x72674  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((uint32_t)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}

extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_unlock_valid(unsigned int*);
extern int z_spin_lock_set_owner(unsigned int*);
extern int z_ready_thread_locked();
extern int z_reschedule(unsigned int*,int);
extern int z_unpend_first_thread(unsigned int*);
extern unsigned int* FUN_00075944(int,int);
extern int assert_post_action(int,int);
extern int printk(int,...);
extern int z_handle_obj_poll_events(unsigned int*,int);

unsigned int FUN_00072674(unsigned int *param_1, unsigned int *param_2, unsigned int *param_3, int param_4, char param_5)
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
  if (bVar1 && (uVar4 = getBasePriority(), uVar4 == 0 || 0x20 < uVar4)) {
    setBasePriority(0x20);
  }
  InstructionSynchronizationBarrier(0xf);
  iVar2 = z_spin_lock_valid(puVar5);
  if (iVar2 == 0) {
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0920) /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
    printk(((unsigned long)&rodata_f0935) /*=0xf0935*/, puVar5);
    uVar6 = 0x72;
LAB_726b6:
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, uVar6);
  }
  z_spin_lock_set_owner(puVar5);
  if (param_5 != 0) {
    param_2 = (unsigned int*)param_1[1];
  }
  iVar2 = (int)z_unpend_first_thread(param_1 + 3);
  if (iVar2 != 0) {
    *(unsigned int**)(iVar2 + 0x14) = param_3;
    *(unsigned int*)(iVar2 + 0x90) = 0;
    z_ready_thread_locked();
    goto LAB_726e2;
  }
  if (param_4 == 0) {
    *param_3 = 0;
  } else {
    puVar3 = FUN_00075944(0, 8);
    if (puVar3 == 0) {
      iVar2 = z_spin_unlock_valid(puVar5);
      if (iVar2 != 0) {
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority(uVar6);
        }
        InstructionSynchronizationBarrier(0xf);
        return 0xfffffff4;
      }
      printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f08f4) /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
      printk(((unsigned long)&rodata_f090b) /*=0xf090b*/, puVar5);
      uVar6 = 0xf0;
      goto LAB_726b6;
    }
    puVar3[1] = (unsigned int)(unsigned long)param_3;
    *puVar3 = 1;
    param_3 = puVar3;
  }
  uVar4 = *param_3 & 3;
  if (param_2 == 0) {
    *param_3 = *param_1 | uVar4;
    *param_1 = (unsigned int)(unsigned long)param_3;
    if (param_1[1] == 0) {
LAB_72748:
      param_1[1] = (unsigned int)(unsigned long)param_3;
    }
  } else if (*param_2 < 4) {
    *param_3 = uVar4;
    puVar3 = (unsigned int*)param_1[1];
    if (puVar3 != 0) {
      *puVar3 = (*puVar3 & 3) | (unsigned int)(unsigned long)param_3;
      goto LAB_72748;
    }
    *param_1 = (unsigned int)(unsigned long)param_3;
    param_1[1] = (unsigned int)(unsigned long)param_3;
  } else {
    *param_3 = (*param_2 & 0xfffffffc) | uVar4;
    *param_2 = (unsigned int)(unsigned long)param_3 | (*param_2 & 3);
  }
  z_handle_obj_poll_events(param_1 + 5, 4);
LAB_726e2:
  z_reschedule(puVar5, uVar6);
  return 0;
}
