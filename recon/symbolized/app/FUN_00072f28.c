#include "g1_app_symbols.h"
/* named: FUN_00072f28 */
/* Reconstructed FUN_00072f28 @ 0x72f28  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern void printk(u32,u32,...);
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(u32);
extern void z_spin_lock_set_owner(u32);
extern int z_spin_unlock_valid(u32);
extern u32 FUN_00072cd4(int,void*);
static inline u32 rd_basepri(void){u32 v;__asm__ volatile("mrs %0, basepri":"=r"(v));return v;}
static inline void wr_basepri_max(u32 v){__asm__ volatile("msr basepri_max, %0"::"r"(v):"memory");}
static inline void wr_basepri(u32 v){__asm__ volatile("msr basepri, %0"::"r"(v):"memory");}
static inline void isb_(void){__asm__ volatile("isb");}
u32 FUN_00072f28(u32 param_1, int param_2, u32 param_3){
    u32 local_14 = param_1;
    u32 uStack_10 = param_3;
    (void)uStack_10;
    u32 uVar4, uVar5;
    if(param_2==0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "work != ((void *)0)" /*=0xf82e0*/, "WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/, 0x174, param_1);
        uVar4=0x174; uVar5="WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/;
    } else {
        uVar5 = rd_basepri();
        wr_basepri_max(0x20);
        isb_();
        int iVar3 = z_spin_lock_valid(((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
        if(iVar3==0){
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_lock_valid(l)" /*=0xf0920*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72, param_1);
            printk("\tInvalid spinlock %p\n" /*=0xf0935*/, ((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
            uVar4=0x72; uVar5="WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/;
        } else {
            z_spin_lock_set_owner(((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
            uVar4 = FUN_00072cd4(param_2, &local_14);
            iVar3 = z_spin_unlock_valid(((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
            if(iVar3!=0){
                wr_basepri(uVar5);
                isb_();
                return uVar4;
            }
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0, param_1);
            printk("\tNot my spinlock %p\n" /*=0xf090b*/, ((uintptr_t)&timer_spinlock) /*=0x2000b480*/);
            uVar4=0xf0; uVar5="WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/;
        }
    }
    assert_post_action(uVar5, uVar4);
    return 0;
}

