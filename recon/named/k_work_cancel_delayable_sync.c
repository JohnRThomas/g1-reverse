/* readable reconstruction; identity: FUN_000735cc @ 0x000735cc
 * public-name: k_work_cancel_delayable_sync
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_impl_k_sem_take                        <= FUN_00072908 @ 0x00072908
 *   cancel_sync_locked                       <= FUN_00072c98 @ 0x00072c98
 *   k_work_cancel_delayable_sync             <= FUN_000735cc @ 0x000735cc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 *   unschedule_locked                        <= FUN_0008656a @ 0x0008656a
 *   cancel_async_locked                      <= FUN_00086596 @ 0x00086596
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f3d75                             @ 0x000f3d75
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f8291                             @ 0x000f8291
 *   rodata_f82df                             @ 0x000f82df
 *   timer_spinlock                           @ 0x2000b480
 */
/* Reconstructed FUN_000735cc @ 0x735cc */
#include <stdint.h>
#include <stdbool.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int k_is_in_isr(void); extern int z_spin_lock_valid(uint32_t); extern void z_spin_lock_set_owner(uint32_t); extern uint64_t z_spin_unlock_valid(uint32_t);
extern void unschedule_locked(void*); extern void cancel_async_locked(void*); extern int cancel_sync_locked(void*,void*); extern void z_impl_k_sem_take(void*,uint32_t,uint32_t,uint32_t);
extern void printk(uint32_t,...); extern void assert_post_action(uint32_t,uint32_t);
bool k_work_cancel_delayable_sync(uint8_t *obj,uint8_t *request)
{
    if (!obj) { printk(0x99cbd,0xf82df,0xf820f,0x411); assert_post_action(0xf820f,0x411); }
    if (!request) { printk(0x99cbd,0xf8291,0xf820f,0x412); assert_post_action(0xf820f,0x412); }
    if (k_is_in_isr()) { printk(0x99cbd,0xf3d75,0xf820f,0x413); assert_post_action(0xf820f,0x413); }
    uint32_t bp=__get_BASEPRI(); __set_BASEPRI_MAX(0x20); __ISB();
    if (!z_spin_lock_valid(0x2000b480)) { printk(0x99cbd,0xf0920,0xf08c7,0x72); printk(0xf0935,0x2000b480); assert_post_action(0xf08c7,0x72); }
    z_spin_lock_set_owner(0x2000b480); bool active=(*(uint32_t *)(obj+0xc)&0xf)!=0; int notify=0;
    if (active) { unschedule_locked(obj); cancel_async_locked(obj); notify=cancel_sync_locked(obj,request); }
    uint64_t unlock=z_spin_unlock_valid(0x2000b480);
    if (!(uint32_t)unlock) { printk(0x99cbd,0xf08f4,0xf08c7,0xf0); printk(0xf090b,0x2000b480); assert_post_action(0xf08c7,0xf0); }
    __set_BASEPRI(bp); __ISB();
    if (notify) z_impl_k_sem_take(request+8,(uint32_t)(unlock>>32),UINT32_MAX,UINT32_MAX);
    return active;
}
