#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00073518 @ 0x00073518
 * public-name: k_work_cancel_delayable
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_work_cancel_delayable                  <= FUN_00073518 @ 0x00073518
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   unschedule_locked                        <= FUN_0008656a @ 0x0008656a
 *   cancel_async_locked                      <= FUN_00086596 @ 0x00086596
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f82df                             @ 0x000f82df
 *   timer_spinlock                           @ 0x2000b480
 */
/* Reconstructed FUN_00073518 @ 0x73518  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_log.h"
typedef uint32_t u32;
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(u32);
extern void z_spin_lock_set_owner(u32);
extern int z_spin_unlock_valid(u32);
extern void unschedule_locked(int);
extern u32 cancel_async_locked(int);
u32 k_work_cancel_delayable(int param_1, u32 param_2, u32 param_3, u32 param_4){
    u32 uVar4, uVar5;
    if(param_1==0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f82df) /*=0xf82df*/, ((unsigned long)&rodata_f820f) /*=0xf820f*/, 0x400, param_4);
        assert_post_action(((unsigned long)&rodata_f820f) /*=0xf820f*/, 0x400);
    }
    {
        uVar5 = __get_BASEPRI();
        __set_BASEPRI_MAX(0x20);
        __ISB();
        int iVar3 = z_spin_lock_valid(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
        if(iVar3==0){
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72, param_4);
            printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/, ((unsigned long)&timer_spinlock) /*=0x2000b480*/);
            uVar4=0x72; uVar5=((unsigned long)&rodata_f08c7) /*=0xf08c7*/;
        } else {
            z_spin_lock_set_owner(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
            unschedule_locked(param_1);
            uVar4 = cancel_async_locked(param_1);
            iVar3 = z_spin_unlock_valid(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
            if(iVar3!=0){
                __set_BASEPRI(uVar5);
                __ISB();
                return uVar4;
            }
            printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
            printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/, ((unsigned long)&timer_spinlock) /*=0x2000b480*/);
            uVar4=0xf0; uVar5=((unsigned long)&rodata_f08c7) /*=0xf08c7*/;
        }
    }
    assert_post_action(uVar5, uVar4);
    return 0;
}
