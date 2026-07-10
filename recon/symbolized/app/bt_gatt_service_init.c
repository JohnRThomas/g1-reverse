#include "g1_app_symbols.h"
/* named: bt_gatt_service_init */
/* Reconstructed bt_gatt_service_init @ 0x59cb4  (parity: 300/300 trials, PROVEN) */

extern unsigned long long atomic_or_0(int a, int b);
extern void printk(int a, int b, int c, int d);
extern void assert_post_action(int a, int b);

void bt_gatt_service_init(void)
{
    unsigned long long uVar5;
    unsigned short sVar2;
    int bVar3;
    unsigned int uVar4;

    uVar5 = atomic_or_0(((uintptr_t)&gatt_service_init_guard) /*=0x2000af04*/, 2);
    if (((unsigned int)uVar5 & (unsigned int)(uVar5 >> 32)) == 0) {
        sVar2 = *(volatile unsigned short *)((uintptr_t)&last_static_handle) /*=0x2000ff3c*/;
        bVar3 = 0;
        uVar4 = ((uintptr_t)&tbl_88058) /*=0x88058*/;
        while (1) {
            if (((uintptr_t)&tbl_88058) /*=0x88070*/ < uVar4) {
                if (bVar3) {
                    *(volatile unsigned short *)((uintptr_t)&last_static_handle) /*=0x2000ff3c*/ = sVar2;
                }
                printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/, "svc <= _bt_gatt_service_static_list_end" /*=0xf49ac*/, "WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0x5ad);
                printk("\tunexpected list end location\n" /*=0xf0d20*/, 0, 0, 0);
                assert_post_action("WEST_TOPDIR/zephyr/subsys/bluetooth/host/gatt.c" /*=0xf46b8*/, 0x5ad);
            }
            if (((uintptr_t)&tbl_88058) /*=0x88070*/ <= uVar4) break;
            sVar2 = (unsigned short)(sVar2 + *(int *)(uVar4 + 4));
            uVar4 = uVar4 + 8;
            bVar3 = 1;
        }
        if (bVar3) {
            *(volatile unsigned short *)((uintptr_t)&last_static_handle) /*=0x2000ff3c*/ = sVar2;
        }
    }
}

