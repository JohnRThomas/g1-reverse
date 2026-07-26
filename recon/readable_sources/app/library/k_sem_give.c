#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_kernel_obj_shared_param__param_0167    [param_0167; library]
 * Raw function identity: 0x00072880.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00072880 @ 0x00072880
 * public-name: k_sem_give
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   z_ready_thread_locked                    <= FUN_000738d4 @ 0x000738d4
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   z_unpend_first_thread                    <= FUN_000744a4 @ 0x000744a4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_handle_obj_poll_events                 <= FUN_0008688e @ 0x0008688e
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   g_mutex_lock_spinlock                    @ 0x2000b474
 */
/* Reconstructed FUN_00072880 @ 0x72880  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../../headers/g1_log.h"
extern int z_spin_lock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void z_ready_thread_locked(void);
extern void z_reschedule(int,int);
extern int z_unpend_first_thread(int);
extern void assert_post_action(int,int);
extern void z_handle_obj_poll_events(int,int);
void k_sem_give(int object)
{
  unsigned int previous_priority = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();

  if (z_spin_lock_valid(((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/) == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
    printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/, ((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
    return;
  }

  z_spin_lock_set_owner(((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/);
  int entry = z_unpend_first_thread(object);
  if (entry == 0) {
    unsigned int completed = *(volatile unsigned int *)(object + 8);
    if (*(volatile unsigned int *)(object + 12) != completed) {
      completed++;
    }
    *(volatile unsigned int *)(object + 8) = completed;
    z_handle_obj_poll_events(object + 0x10, 2);
  } else {
    *(volatile unsigned int *)(entry + 0x90) = 0;
    z_ready_thread_locked();
  }
  z_reschedule(((unsigned long)&g_mutex_lock_spinlock) /*=0x2000b474*/, previous_priority);
}
