#include "g1_app_symbols.h"
/* named: k_queue_insert_with_timeout */
/* Reconstructed k_queue_insert_with_timeout @ 0x5eeb4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(void);
extern int z_spin_unlock_valid(void);
extern void z_spin_lock_set_owner(void);
extern int FUN_000727ac(void);
extern void assert_post_action(void);
extern void printk(void);
extern void k_queue_prepend(void);
extern void sys_timepoint_calc(void);
extern void sys_timepoint_timeout(void);

int k_queue_insert_with_timeout(int param_1, unsigned param_2, int param_3, int param_4)
{
    unsigned local_24 = param_2;
    int r4 = 0;
    int iVar6;
    unsigned uVar_h, uVar2, uVar1;

    sys_timepoint_calc();
    if (param_1 == 0) {
        printk();
        goto EF12;
    }
    {
        int iVar6b = z_spin_lock_valid();
        if (iVar6b == 0) {
            printk();
            printk();
            goto EF12;
        }
    }
    z_spin_lock_set_owner();
    uVar_h = *(volatile uint16_t*)(param_1 + 0x22);
    if (uVar_h == 0) {
        int t = z_spin_unlock_valid();
        if (t == 0) goto EF40;
        r4 = FUN_000727ac();
        if (r4 != 0) goto EF60;
        return 0;
    } else {
        uVar2 = *(volatile uint16_t*)(param_1 + 0x20);
        if (uVar2 <= uVar_h) goto EFA0;
        r4 = FUN_000727ac();
        if (r4 == 0) goto EFA0;
        {
            int t = z_spin_unlock_valid();
            if (t == 0) goto EF40;
            goto EF60;
        }
    }
EFA0:
    uVar1 = *(volatile uint16_t*)(param_1 + 0x22);
    *(volatile uint16_t*)(param_1 + 0x22) = (uint16_t)(uVar1 - 1);
    {
        int t = z_spin_unlock_valid();
        if (t == 0) goto EF40;
    }
    {
        unsigned p20 = *(volatile uint16_t*)(param_1 + 0x20);
        unsigned mul = ((unsigned)*(volatile uint8_t*)(param_1 + 0x24) + 0x1b) & 0xfffffffc;
        int d = ((int)(param_1 - ((uintptr_t)&acl_tx_pool) /*=0x20003a7c*/)) >> 2;
        r4 = (int)((p20 - uVar1) * mul) + *(volatile int*)(param_1 + 0x30);
        *(volatile int8_t*)(r4 + 10) = (int8_t)((uint32_t)0xc4ec4ec5 * (uint32_t)d);
        *(volatile uint8_t*)(r4 + 0xb) = *(volatile uint8_t*)(param_1 + 0x24);
    }
    goto EF60;
EF60:
    {
        unsigned r5v = local_24;
        if (r5v == 0) {
            *(volatile int*)(r4 + 0x14) = 0;
            goto EF2E;
        }
        sys_timepoint_timeout();
        {
            unsigned idx = *(volatile uint8_t*)(r4 + 0xa);
            int p = *(volatile int*)(0x34 * idx + ((uintptr_t)&acl_tx_pool) /*=0x20003a7c*/ + 0x2c);
            int p2 = *(volatile int*)p;
            int fn = *(volatile int*)p2;
            iVar6 = ((int(*)(int,int,int,int))(intptr_t)fn)(r4, (int)(intptr_t)&local_24, param_1, param_2);
            *(volatile int*)(r4 + 0x14) = iVar6;
            if (iVar6 == 0) {
                k_queue_prepend();
                return 0;
            }
            if (r5v <= local_24) goto EF2E;
            printk();
            printk();
            goto EF12;
        }
    }
EF2E:
    *(volatile int*)(r4 + 4) = 0;
    *(volatile uint16_t*)(r4 + 8) = 1;
    *(volatile uint16_t*)(r4 + 0x10) = 0;
    *(volatile uint16_t*)(r4 + 0x12) = (uint16_t)local_24;
    *(volatile int*)(r4 + 0xc) = *(volatile int*)(r4 + 0x14);
    return r4;
EF40:
    printk();
    printk();
    goto EF12;
EF12:
    assert_post_action();
    return 0;
}

