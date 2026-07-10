#include "g1_app_symbols.h"
/* named: sys_rand32_get */
/* globals referenced:
//   0x00087b90  entropy_dev                  
*/
/* Reconstructed sys_rand32_get @ 0x52c40  (parity: 300/300 trials, PROVEN) */

extern int entropy_get_entropy_isr_call(int*);
extern void assert_post_action(int,int);
extern void printk(int, ...);
extern int sys_clock_cycle_get_32(void);
extern int z_device_is_ready(int);

int sys_rand32_get(int param_1, int param_2)
{
    int local_c = param_2;
    int iVar2;
    iVar2 = z_device_is_ready(((uintptr_t)&entropy_dev) /*=0x87b90*/);
    if (iVar2 == 0) {
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "device_is_ready(entropy_dev)" /*=0xf2af8*/, "WEST_TOPDIR/zephyr/subsys/random/rand32_entropy_device.c" /*=0xf2abf*/, 0x15, param_1);
        printk("\tEntropy device %s not ready\n" /*=0xf2b15*/, *(volatile int*)((uintptr_t)&entropy_dev) /*=0x87b90*/);
        assert_post_action("WEST_TOPDIR/zephyr/subsys/random/rand32_entropy_device.c" /*=0xf2abf*/, 0x15);
    }
    iVar2 = entropy_get_entropy_isr_call(&local_c);
    if (iVar2 < 0) {
        local_c = sys_clock_cycle_get_32();
    }
    return local_c;
}

