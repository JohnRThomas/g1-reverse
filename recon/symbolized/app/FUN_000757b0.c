#include "g1_app_symbols.h"
/* named: FUN_000757b0 */
/* Reconstructed FUN_000757b0 @ 0x757b0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern void printk(u32,u32,...);
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(u32);
extern void z_spin_lock_set_owner(u32);
extern int z_spin_unlock_valid(u32);
extern u32 signal_poll_event(void);
extern void z_reschedule(u32,u32);
static inline u32 rd_basepri(void){u32 v;__asm__ volatile("mrs %0, basepri":"=r"(v));return v;}
static inline void wr_basepri_max(u32 v){__asm__ volatile("msr basepri_max, %0"::"r"(v):"memory");}
static inline void wr_basepri(u32 v){__asm__ volatile("msr basepri, %0"::"r"(v):"memory");}
static inline void isb_(void){__asm__ volatile("isb");}
u32 FUN_000757b0(int* param_1, int param_2){
    u32 uVar7 = rd_basepri();
    wr_basepri_max(0x20);
    isb_();
    int iVar3 = z_spin_lock_valid(((uintptr_t)&poll_spinlock) /*=0x2000b4a0*/);
    if(iVar3 != 0){
        z_spin_lock_set_owner(((uintptr_t)&poll_spinlock) /*=0x2000b4a0*/);
        int* piVar4 = (int*)*param_1;
        param_1[3] = param_2;
        param_1[2] = 1;
        u32 uVar6;
        if(param_1 == piVar4){
            iVar3 = z_spin_unlock_valid(((uintptr_t)&poll_spinlock) /*=0x2000b4a0*/);
            if(iVar3 == 0){
                printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
                printk("\tNot my spinlock %p\n" /*=0xf090b*/, ((uintptr_t)&poll_spinlock) /*=0x2000b4a0*/);
                assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
                return 0;
            }
            wr_basepri(uVar7);
            isb_();
            uVar6 = 0;
        } else {
            int iVar3b = *piVar4;
            int* piVar5 = (int*)piVar4[1];
            *piVar5 = iVar3b;
            *(int**)(iVar3b+4) = piVar5;
            piVar4[0] = 0;
            piVar4[1] = 0;
            uVar6 = signal_poll_event();
            z_reschedule(((uintptr_t)&poll_spinlock) /*=0x2000b4a0*/, uVar7);
        }
        return uVar6;
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_lock_valid(l)" /*=0xf0920*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72);
    printk("\tInvalid spinlock %p\n" /*=0xf0935*/, ((uintptr_t)&poll_spinlock) /*=0x2000b4a0*/);
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72);
    return 0;
}

