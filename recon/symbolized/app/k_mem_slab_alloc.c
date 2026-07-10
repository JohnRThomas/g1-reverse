#include "g1_app_symbols.h"
/* named: k_mem_slab_alloc */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
*/
/* Reconstructed k_mem_slab_alloc @ 0x71c20  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern int FUN_00073f6c(int,unsigned,int,int,int,int,int);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);

int k_mem_slab_alloc(int param_1, int *param_2, int param_3, int param_4){
    int iVar6 = param_1 + 8;
    unsigned uVar7 = 0;
    int iVar3 = z_spin_lock_valid(iVar6);
    if (iVar3 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_lock_valid(l)" /*=0xf0920*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72, param_1, param_2);
        printk("\tInvalid spinlock %p\n" /*=0xf0935*/, iVar6);
        uVar7=0x72;
        assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, uVar7);
        return 0x72;
    }
    z_spin_lock_set_owner(iVar6);
    int *puVar4 = *(int**)(param_1+0x18);
    int ret;
    if (puVar4 == 0){
        if (param_3 != 0 || param_4 != 0){
            int r = FUN_00073f6c(iVar6, uVar7, param_1, 0, param_3, param_4, param_3);
            if (r != 0) return r;
            *param_2 = *(int*)(*(int*)(((uintptr_t)&g_zephyr_kernel) /*=0x2000b448*/+8)+0x14);
            return 0;
        }
        ret = -0xc;
        *param_2 = 0;
    } else {
        *param_2 = (int)puVar4;
        *(int*)(param_1+0x18) = *puVar4;
        *(int*)(param_1+0x1c) = *(int*)(param_1+0x1c) + 1;
        ret = 0;
    }
    iVar3 = z_spin_unlock_valid(iVar6);
    if (iVar3 != 0){
        return ret;
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0, param_1, param_2);
    printk("\tNot my spinlock %p\n" /*=0xf090b*/, iVar6);
    uVar7=0xf0;
    assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, uVar7);
    return ret;
}

