/* readable reconstruction; identity: FUN_000729fc @ 0x000729fc
 * public-name: queue_cancel_wait_locked
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   queue_cancel_wait_locked                 <= FUN_000729fc @ 0x000729fc
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
/* Reconstructed FUN_000729fc @ 0x729fc
 * CFG_VERIFY_PREFIX_FIRST: drains callback-owned queue until it reports empty. */
#include <stdint.h>
#include <cmsis_gcc.h>
extern int z_spin_lock_valid(uint32_t); extern void z_spin_lock_set_owner(uint32_t);
extern int z_unpend_first_thread(void *); extern void z_ready_thread_locked(void);
extern void z_handle_obj_poll_events(void *, int); extern void z_reschedule(uint32_t,uint32_t);
extern void printk(uint32_t,...); extern void assert_post_action(uint32_t,uint32_t);
void queue_cancel_wait_locked(uint8_t *queue)
{
    uint32_t bp=__get_BASEPRI(); __set_BASEPRI_MAX(0x20); __ISB();
    if (!z_spin_lock_valid(0x2000b474)) { printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0xf08c7,0x72); printk(((unsigned long)"\tInvalid spinlock %p\n"),0x2000b474); assert_post_action(0xf08c7,0x72); }
    z_spin_lock_set_owner(0x2000b474);
    uint8_t *p; while ((p=(uint8_t *)(uintptr_t)z_unpend_first_thread(queue)) != 0) { *(uint32_t *)(p+0x90)=0xfffffff5; z_ready_thread_locked(); }
    *(uint32_t *)(queue+8)=0; z_handle_obj_poll_events(queue+0x10,2); z_reschedule(0x2000b474,bp);
}
