#include "g1_app_symbols.h"
/* named: smp_transport_init */
/* Reconstructed smp_transport_init @ 0x526f4  (parity: 300/300 trials, PROVEN) */

extern void k_work_init(int a, unsigned int b);
extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_00080b28(void);
extern void z_impl_k_queue_init(int a);

unsigned int smp_transport_init(int param_1)
{
    if (*(volatile int *)(param_1 + 0x2c) == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "(smpt->functions.output != ((void *)0))" /*=0xf293b*/, "WEST_TOPDIR/zephyr/subsys/mgmt/mcumgr/transport/src/smp.c" /*=0xf2901*/, 0x92);
        printk("\tRequired transport output function pointer cannot be NULL\n" /*=0xf2963*/, 0, 0, 0);
        assert_post_action("WEST_TOPDIR/zephyr/subsys/mgmt/mcumgr/transport/src/smp.c" /*=0xf2901*/, 0x92);
    }
    FUN_00080b28();
    k_work_init(param_1, ((uintptr_t)&rodata_80ab5) /*=0x80ab5*/);
    z_impl_k_queue_init(param_1 + 0x10);
    return 0;
}

