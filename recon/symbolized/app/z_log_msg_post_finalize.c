#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d7d8 @ 0x0004d7d8
 * public-name: z_log_msg_post_finalize
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_process                              <= FUN_0004d594 @ 0x0004d594
 *   z_log_msg_post_finalize                  <= FUN_0004d7d8 @ 0x0004d7d8
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_sem_give                               <= FUN_00072880 @ 0x00072880
 *   z_impl_k_timer_start                     <= FUN_00075174 @ 0x00075174
 *   atomic_inc                               <= FUN_0007ee2c @ 0x0007ee2c
 *   z_impl_k_timer_stop                      <= FUN_0008673e @ 0x0008673e
 * address symbols (name @ address):
 *   g_200039f8                               @ 0x200039f8
 *   g_200056a8                               @ 0x200056a8
 *   g_2000a0c8                               @ 0x2000a0c8
 *   g_2000a0d0                               @ 0x2000a0d0
 *   log_buffered_cnt                         @ 0x2000a0d8
 *   g_log_initialized_flag                   @ 0x2001d44c
 */
/* Reconstructed FUN_0004d7d8 @ 0x0004d7d8 (z_log_msg_post_finalize).
 * Exact configured Zephyr log_core.c static owner; extent 0xb0.
 */
#include <stdint.h>
extern uint32_t atomic_inc(volatile uint32_t *); /* atomic_inc */
extern int z_spin_lock_valid(unsigned int*);                 /* z_spin_lock_valid */
extern int z_spin_lock_set_owner(unsigned int*);                 /* z_spin_lock_set_owner */
extern void z_spin_unlock_valid(void *);                 /* z_spin_unlock_valid */
extern int log_process(void);                   /* log_process */
extern void z_impl_k_timer_start(void *, uint32_t, uint32_t, uint32_t); /* k_timer_start */
extern void z_impl_k_timer_stop(void *);                 /* k_timer_stop */
extern void k_sem_give(int);                 /* k_sem_give */

void z_log_msg_post_finalize(void)
{
    uint32_t previous = atomic_inc((volatile uint32_t *)((unsigned long)&log_buffered_cnt) /*=0x2000a0d8*/);
    if (*(volatile uint8_t *)((unsigned long)&g_log_initialized_flag) /*=0x2001d44c*/ != 0U) {
        /* The shipped k_spin_lock/unlock expansion surrounds log_process. */
        z_spin_lock_valid((void *)((unsigned long)&g_2000a0c8) /*=0x2000a0c8*/);
        z_spin_lock_set_owner((void *)((unsigned long)&g_2000a0c8) /*=0x2000a0c8*/);
        log_process();
        z_spin_unlock_valid((void *)((unsigned long)&g_2000a0c8) /*=0x2000a0c8*/);
        return;
    }
    if (*(volatile uintptr_t *)((unsigned long)&g_2000a0d0) /*=0x2000a0d0*/ == 0U)
        return;
    if (previous == 0U) {
        z_impl_k_timer_start((void *)((unsigned long)&g_200056a8) /*=0x200056a8*/, 0x8000U, 0U, 0U);
    } else if (previous == 9U) {
        z_impl_k_timer_stop((void *)((unsigned long)&g_200056a8) /*=0x200056a8*/);
        k_sem_give((void *)((unsigned long)&g_200039f8) /*=0x200039f8*/);
    }
}
