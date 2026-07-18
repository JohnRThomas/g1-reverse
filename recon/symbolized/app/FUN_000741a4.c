#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000741a4 @ 0x000741a4
 * public-name: FUN_000741a4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   dlist_unlink_node                        <= FUN_00073cdc @ 0x00073cdc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_reschedule_unlocked                    <= FUN_0008664c @ 0x0008664c
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   g_zephyr_kernel                          @ 0x2000b448
 *   g_sched_ready_runq                       @ 0x2000b464
 *   sched_spinlock_b490                      @ 0x2000b490
 */
/* Reconstructed FUN_000741a4 @ 0x741a4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void FUN_000737d8(int);
extern void dlist_unlink_node(void*,void*);
extern void FUN_00074d74(void*);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern void z_reschedule_unlocked(void);

void FUN_000741a4(uint8_t *param_1){
    unsigned uVar6=0;
    FUN_00074d74(param_1+0x18);
    int iVar4 = z_spin_lock_valid((void*)((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
    if (iVar4==0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f0920) /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
        printk(((unsigned long)&rodata_f0935) /*=0xf0935*/,((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
        uVar6=0x72;
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,uVar6);
        return;
    }
    z_spin_lock_set_owner((void*)((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
    if ((int8_t)param_1[0xd] < 0){
        param_1[0xd] = param_1[0xd] & 0x7f;
        dlist_unlink_node((void*)((unsigned long)&g_sched_ready_runq) /*=0x2000b464*/, param_1);
    }
    int iVar5 = *(int*)(((unsigned long)&g_zephyr_kernel) /*=0x2000b448*/+8);
    param_1[0xd] = param_1[0xd] | 0x10;
    FUN_000737d8(iVar5 == (int)(intptr_t)param_1);
    iVar5 = z_spin_unlock_valid((void*)((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
    if (iVar5 != 0){
        if (*(int*)(((unsigned long)&g_zephyr_kernel) /*=0x2000b448*/+8) != (int)(intptr_t)param_1) return;
        z_reschedule_unlocked();
        return;
    }
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f08f4) /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
    printk(((unsigned long)&rodata_f090b) /*=0xf090b*/,((unsigned long)&sched_spinlock_b490) /*=0x2000b490*/);
    uVar6=0xf0;
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,uVar6);
}
