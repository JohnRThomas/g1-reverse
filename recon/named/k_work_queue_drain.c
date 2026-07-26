/* readable reconstruction; identity: FUN_000731b8 @ 0x000731b8
 * public-name: k_work_queue_drain
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_work_queue_drain                       <= FUN_000731b8 @ 0x000731b8
 *   z_sched_wait                             <= FUN_00074b10 @ 0x00074b10
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   k_is_in_isr                              <= FUN_00086406 @ 0x00086406
 *   notify_queue_locked                      <= FUN_00086588 @ 0x00086588
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f3d75                             @ 0x000f3d75
 *   rodata_f586b                             @ 0x000f586b
 *   rodata_f820f                             @ 0x000f820f
 *   timer_spinlock                           @ 0x2000b480
 */
/* Reconstructed FUN_000731b8 @ 0x731b8 */
#include <stdint.h>
#include <cmsis_gcc.h>
extern int k_is_in_isr(void); extern int z_spin_lock_valid(uint32_t); extern void z_spin_lock_set_owner(uint32_t); extern int z_spin_unlock_valid(uint32_t);
extern void notify_queue_locked(void *); extern uint32_t z_sched_wait(uint32_t,uint32_t,void*,uint32_t,uint32_t,uint32_t,uint32_t);
extern void printk(uint32_t,...); extern void assert_post_action(uint32_t,uint32_t);
uint32_t k_work_queue_drain(uint8_t *obj, int requested, uint32_t a, uint32_t b)
{
    if (!obj) { printk(0x99cbd,0xf586b,0xf820f,0x2ed,0,requested,a,b); assert_post_action(0xf820f,0x2ed); }
    if (k_is_in_isr()) { printk(0x99cbd,0xf3d75,0xf820f,0x2ee,obj,requested,a,b); assert_post_action(0xf820f,0x2ee); }
    uint32_t bp=__get_BASEPRI(); __set_BASEPRI_MAX(0x20); __ISB();
    if (!z_spin_lock_valid(0x2000b480)) { printk(0x99cbd,0xf0920,0xf08c7,0x72,obj,requested,a,b); printk(0xf0935,0x2000b480); assert_post_action(0xf08c7,0x72); }
    z_spin_lock_set_owner(0x2000b480); uint32_t flags=*(uint32_t *)(obj+0xf0);
    if (!(flags&6)) {
        if (!requested && !*(uint32_t *)(obj+0xd8)) {
            if (z_spin_unlock_valid(0x2000b480)) { __set_BASEPRI(bp); __ISB(); return 0; }
            printk(0x99cbd,0xf08f4,0xf08c7,0xf0,obj,requested,a,b); printk(0xf090b,0x2000b480); assert_post_action(0xf08c7,0xf0);
        }
        flags |= requested ? 0xc : 4;
    } else { *(uint32_t *)(obj+0xf0)=flags|4; if (requested) flags|=0xc; else goto run; }
    *(uint32_t *)(obj+0xf0)=flags;
run: notify_queue_locked(obj); return z_sched_wait(0x2000b480,bp,obj+0xe8,UINT32_MAX,UINT32_MAX,UINT32_MAX,0);
}
