#include "g1_app_symbols.h"
/* named: FUN_0004ba38 */
/* Reconstructed FUN_0004ba38 @ 0x4ba38  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004b4fc(int,int,unsigned,int,unsigned);
extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,...);

unsigned FUN_0004ba38(int param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    int iVar7 = param_1 + 0x14;
    unsigned uVar8 = 0;
    int iVar4 = z_spin_lock_valid(iVar7);
    unsigned uVar5 = 0;
    if (iVar4 == 0){
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_lock_valid(l)" /*=0xf0920*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0x72);
        printk("\tInvalid spinlock %p\n" /*=0xf0935*/, iVar7);
        uVar5=0x72; uVar8="WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/;
        assert_post_action(uVar8, uVar5);
        return uVar5;
    }
    z_spin_lock_set_owner(iVar7);
    unsigned uVar6 = *(unsigned short*)(param_1+0x1c) & 7;
    if (uVar6 == 2){
        short sVar1 = *(short*)(param_1+0x1e);
        if (sVar1 == 0){
            printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "mgr->refs > 0" /*=0xf094b*/, "WEST_TOPDIR/zephyr/lib/os/onoff.c" /*=0xf0824*/, 0x1ef);
            assert_post_action("WEST_TOPDIR/zephyr/lib/os/onoff.c" /*=0xf0824*/, 0x1ef);
        }
        unsigned short nv = (unsigned short)(sVar1 - 1);
        *(short*)(param_1+0x1e) = (short)nv;
        uVar5 = 2;
        if (nv == 0){
            FUN_0004b4fc(param_1, 2, uVar8, 0, param_4);
            return 2;
        }
    } else if (uVar6 == 1){
        uVar5 = 0xfffffffb;
    } else {
        uVar5 = 0xffffff7a;
    }
    iVar4 = z_spin_unlock_valid(iVar7);
    if (iVar4 != 0){
        return uVar5;
    }
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "z_spin_unlock_valid(l)" /*=0xf08f4*/, "WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/, 0xf0);
    printk("\tNot my spinlock %p\n" /*=0xf090b*/, iVar7);
    uVar5=0xf0; uVar8="WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/;
    assert_post_action(uVar8, uVar5);
    return uVar5;
}

