/* readable reconstruction; identity: FUN_000741a4 @ 0x000741a4
 * public-name: z_thread_suspend
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   sched_update_cache                       <= FUN_000737d8 @ 0x000737d8
 *   dlist_unlink_node                        <= FUN_00073cdc @ 0x00073cdc
 *   z_thread_suspend                         <= FUN_000741a4 @ 0x000741a4
 *   z_abort_timeout                          <= FUN_00074d74 @ 0x00074d74
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_reschedule_unlocked                    <= FUN_0008664c @ 0x0008664c
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   _kernel                                  @ 0x2000b448
 *   g_sched_ready_runq                       @ 0x2000b464
 *   sched_spinlock                           @ 0x2000b490
 */
/* Reconstructed FUN_000741a4 @ 0x741a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void sched_update_cache(int);
extern void dlist_unlink_node(void*,void*);
extern void z_abort_timeout(void*);
extern void assert_post_action(unsigned,unsigned);
extern void z_reschedule_unlocked(void);

void z_thread_suspend(uint8_t *param_1){
    unsigned uVar6=0;
    z_abort_timeout(param_1+0x18);
    int iVar4 = z_spin_lock_valid((void*)0x2000b490);
    if (iVar4==0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0x000f08c7,0x72);
        printk(((unsigned long)"\tInvalid spinlock %p\n"),0x2000b490);
        uVar6=0x72;
        assert_post_action(0x000f08c7,uVar6);
        return;
    }
    z_spin_lock_set_owner((void*)0x2000b490);
    if ((int8_t)param_1[0xd] < 0){
        param_1[0xd] = param_1[0xd] & 0x7f;
        dlist_unlink_node((void*)0x2000b464, param_1);
    }
    int iVar5 = *(int*)(0x2000b448+8);
    param_1[0xd] = param_1[0xd] | 0x10;
    sched_update_cache(iVar5 == (int)(intptr_t)param_1);
    iVar5 = z_spin_unlock_valid((void*)0x2000b490);
    if (iVar5 != 0){
        if (*(int*)(0x2000b448+8) != (int)(intptr_t)param_1) return;
        z_reschedule_unlocked();
        return;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_unlock_valid(l)"),0x000f08c7,0xf0);
    printk(((unsigned long)"\tNot my spinlock %p\n"),0x2000b490);
    uVar6=0xf0;
    assert_post_action(0x000f08c7,uVar6);
}
