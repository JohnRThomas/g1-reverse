#include "g1_app_symbols.h"
/* named: net_buf_slist_get */
/* Reconstructed net_buf_slist_get @ 0x5f148  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32;
extern void printk(u32,u32,...);
extern void assert_post_action(u32,u32);
extern int z_spin_lock_valid(u32);
extern void z_spin_lock_set_owner(u32);
extern int z_spin_unlock_valid(u32);
static inline u32 rd_basepri(void){u32 v;__asm__ volatile("mrs %0, basepri":"=r"(v));return v;}
static inline void wr_basepri_max(u32 v){__asm__ volatile("msr basepri_max, %0"::"r"(v):"memory");}
static inline void wr_basepri(u32 v){__asm__ volatile("msr basepri, %0"::"r"(v):"memory");}
static inline void isb_(void){__asm__ volatile("isb");}
u32* net_buf_slist_get(u32* param_1){
    u32 uVar4, uVar6;
    if(param_1 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "list" /*=0xf3630*/, "WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/, 0x1ba);
        uVar4=0x1ba; uVar6="WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/;
    } else {
        uVar6 = rd_basepri();
        wr_basepri_max(0x20);
        isb_();
        int iVar3 = z_spin_lock_valid(((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
        if(iVar3==0){
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_lock_valid(l)" /*=0xf0920*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72);
            printk("\tInvalid spinlock %p\n" /*=0xf0935*/, ((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
            uVar4=0x72; uVar6="WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/;
        } else {
            z_spin_lock_set_owner(((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
            u32* puVar5 = (u32*)*param_1;
            if(puVar5 != 0){
                uVar4 = *puVar5;
                *param_1 = uVar4;
                if(puVar5 == (u32*)param_1[1]) param_1[1] = uVar4;
            }
            iVar3 = z_spin_unlock_valid(((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
            if(iVar3!=0){
                wr_basepri(uVar6);
                isb_();
                return puVar5;
            }
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
            printk("\tNot my spinlock %p\n" /*=0xf090b*/, ((uintptr_t)&g_net_buf_slist_lock) /*=0x2000b004*/);
            uVar4=0xf0; uVar6="WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/;
        }
    }
    assert_post_action(uVar6, uVar4);
    return 0;
}

