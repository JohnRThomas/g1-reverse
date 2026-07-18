#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00072f28 @ 0x00072f28
 * public-name: z_work_submit_to_queue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   submit_to_queue_locked                   <= FUN_00072cd4 @ 0x00072cd4
 *   z_work_submit_to_queue                   <= FUN_00072f28 @ 0x00072f28
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f82e0                             @ 0x000f82e0
 *   timer_spinlock                           @ 0x2000b480
 */
/* Reconstructed FUN_00072f28 @ 0x72f28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
typedef uint32_t u32;
extern void printk(u32,u32,...);
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(u32);
extern void z_spin_lock_set_owner(u32);
extern int z_spin_unlock_valid(u32);
extern u32 submit_to_queue_locked(int,void*);
static inline u32 rd_basepri(void){return __get_BASEPRI();}
static inline void wr_basepri_max(u32 v){__set_BASEPRI_MAX(v);}
static inline void wr_basepri(u32 v){__set_BASEPRI(v);}
static inline void isb_(void){__ISB();}
u32 z_work_submit_to_queue(u32 param_1, int param_2, u32 param_3){
    struct lookup_key {
        u32 value;
        u32 qualifier;
    } key = { param_1, param_3 };
    u32 uVar4, uVar5;
    if(param_2==0){
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f82e0) /*=0xf82e0*/, ((unsigned long)&rodata_f820f) /*=0xf820f*/, 0x174, param_1);
        assert_post_action(((unsigned long)&rodata_f820f) /*=0xf820f*/, 0x174);
    }

retry:
    uVar5 = rd_basepri();
    wr_basepri_max(0x20);
    isb_();
    {
        int iVar3 = z_spin_lock_valid(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
        if(iVar3==0){
            printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f0920) /*=0xf0920*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72, param_1);
            printk(((unsigned long)&rodata_f0935) /*=0xf0935*/, ((unsigned long)&timer_spinlock) /*=0x2000b480*/);
            assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x72);
            goto retry;
        }
        z_spin_lock_set_owner(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
        uVar4 = submit_to_queue_locked(param_2, &key);
        iVar3 = z_spin_unlock_valid(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
        if(iVar3!=0){
            wr_basepri(uVar5);
            isb_();
            return uVar4;
        }
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f08f4) /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0, param_1);
        printk(((unsigned long)&rodata_f090b) /*=0xf090b*/, ((unsigned long)&timer_spinlock) /*=0x2000b480*/);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
        goto retry;
    }
}
