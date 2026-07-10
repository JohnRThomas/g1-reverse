#include "g1_app_symbols.h"
/* named: dlist_unlink_node */
/* Reconstructed dlist_unlink_node @ 0x73cdc  (parity: 300/300 trials, PROVEN) */

extern void printk(unsigned int a,unsigned int b,unsigned int c,unsigned int d);
extern unsigned long long assert_post_action(unsigned int a,unsigned int b);

void dlist_unlink_node(unsigned int param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
    int *base;
    if ((unsigned int)param_2 == ((uintptr_t)&g_thread_dummy) /*=0x20006720*/) {
        unsigned long long r;
        printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "!z_is_idle_thread_object(thread)" /*=0xf84d6*/, "WEST_TOPDIR/zephyr/kernel/sched.c" /*=0xf82f4*/, 0x484);
        r = assert_post_action("WEST_TOPDIR/zephyr/kernel/sched.c" /*=0xf82f4*/, 0x484);
        base = (int*)(unsigned int)(r >> 32);
    } else {
        base = param_2;
    }
    {
        int iVar2 = *(volatile int*)base;
        int *piVar1 = *(volatile int**)((char*)base + 4);
        *(volatile int*)piVar1 = iVar2;
        *(volatile int**)((unsigned int)iVar2 + 4) = piVar1;
        *(volatile int*)base = 0;
        *(volatile int*)((char*)base + 4) = 0;
    }
}

