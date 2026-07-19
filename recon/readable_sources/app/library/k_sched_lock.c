#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00073bf4 @ 0x00073bf4
 * public-name: k_sched_lock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   sched_update_cache                       <= FUN_000737d8 @ 0x000737d8
 *   k_sched_lock                             <= FUN_00073bf4 @ 0x00073bf4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   z_reschedule_irqlock                     <= FUN_00086634 @ 0x00086634
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f8553                             @ 0x000f8553
 *   _kernel                                  @ 0x2000b448
 *   sched_spinlock                           @ 0x2000b490
 */
/* Reconstructed FUN_00073bf4 @ 0x73bf4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void*);
extern int z_spin_unlock_valid(void*);
extern void z_spin_lock_set_owner(void*);
extern void sched_update_cache(void);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);
extern void z_reschedule_irqlock(unsigned);

void k_sched_lock(void){
    int iVar3 = z_spin_lock_valid((void*)((unsigned long)&sched_spinlock) /*=0x2000b490*/);
    if (iVar3 == 0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0920) /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
        printk(((unsigned long)&rodata_f0935) /*=0xf0935*/, ((unsigned long)&sched_spinlock) /*=0x2000b490*/);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
        return;
    }
    z_spin_lock_set_owner((void*)((unsigned long)&sched_spinlock) /*=0x2000b490*/);
    char cVar1 = *(char*)(*(int*)(((unsigned long)&_kernel) /*=0x2000b448*/+8)+0xf);
    unsigned r2 = (unsigned)*(int*)(((unsigned long)&_kernel) /*=0x2000b448*/+8);
    unsigned r3 = (unsigned char)cVar1;
    if (cVar1 == 0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f8553) /*=0xf8553*/, ((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x3f8);
        printk(((unsigned long)&rodata_f53ff) /*=0xf53ff*/);
        assert_post_action(((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x3f8);
        r2 = ((unsigned long)&rodata_f82f4) /*=0xf82f4*/;
        r3 = 0x3f8;
        /* fall through in emulation (ipsr==0) */
    }
    *(char*)(r2 + 0xf) = (char)(r3 + 1);
    sched_update_cache();
    iVar3 = z_spin_unlock_valid((void*)((unsigned long)&sched_spinlock) /*=0x2000b490*/);
    if (iVar3 != 0){
        z_reschedule_irqlock(0);
        return;
    }
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f08f4) /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
    printk(((unsigned long)&rodata_f090b) /*=0xf090b*/, ((unsigned long)&sched_spinlock) /*=0x2000b490*/);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
}
