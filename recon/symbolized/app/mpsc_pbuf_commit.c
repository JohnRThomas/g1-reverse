#include "g1_app_symbols.h"
/* named: mpsc_pbuf_commit */
/* Reconstructed mpsc_pbuf_commit @ 0x4be0c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
typedef u32 (*fp)(u8*);
extern void printk(u32,u32,...);
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(int);
extern void z_spin_lock_set_owner(int);
extern int z_spin_unlock_valid(int);
extern u32 idx_inc(int,u32,u32);
extern void max_utilization_update(int);
static inline u32 rd_basepri(void){u32 v;__asm__ volatile("mrs %0, basepri":"=r"(v));return v;}
static inline void wr_basepri_max(u32 v){__asm__ volatile("msr basepri_max, %0"::"r"(v):"memory");}
static inline void wr_basepri(u32 v){__asm__ volatile("msr basepri, %0"::"r"(v):"memory");}
static inline void isb_(void){__asm__ volatile("isb");}
void mpsc_pbuf_commit(int param_1, u8* param_2){
    u32 uVar3 = (*(fp*)(param_1+0x1c))(param_2);
    int iVar5 = param_1+0x14;
    u32 uVar6 = rd_basepri();
    wr_basepri_max(0x20);
    isb_();
    int iVar4 = z_spin_lock_valid(iVar5);
    if(iVar4==0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_lock_valid(l)" /*=0xf0920*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72);
        printk("\tInvalid spinlock %p\n" /*=0xf0935*/, iVar5);
        uVar3=0x72;
    } else {
        z_spin_lock_set_owner(iVar5);
        *param_2 = *param_2 | 1;
        uVar3 = idx_inc(param_1, *(u32*)(param_1+4), uVar3);
        *(u32*)(param_1+4) = uVar3;
        max_utilization_update(param_1);
        iVar4 = z_spin_unlock_valid(iVar5);
        if(iVar4!=0){
            wr_basepri(uVar6);
            isb_();
            return;
        }
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
        printk("\tNot my spinlock %p\n" /*=0xf090b*/, iVar5);
        uVar3=0xf0;
    }
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, uVar3);
}

