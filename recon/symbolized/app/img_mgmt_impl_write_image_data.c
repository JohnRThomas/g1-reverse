#include "g1_app_symbols.h"
/* named: img_mgmt_impl_write_image_data */
/* Reconstructed img_mgmt_impl_write_image_data @ 0x518a8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int flash_area_open(void);
extern unsigned FUN_0005169c(void);
extern void assert_post_action(void);
extern void printk(void);
extern void nullsub_3(void);
extern void FUN_0008096a(void);
extern int FUN_00080970(void);
extern unsigned FUN_000809f6(void);
extern unsigned FUN_00080a46(void);
extern int FUN_00080a82(void);
extern int memcmp(void);
extern void memset_bytes(void);

#define P1(k) (*(volatile int*)((char*)param_1 + (k)))
#define P2u(k) (*(volatile uint32_t*)((char*)param_2 + (k)))

unsigned img_mgmt_impl_write_image_data(int *param_1, unsigned *param_2)
{
    volatile uint32_t *puVar1 = (volatile uint32_t*)((uintptr_t)&g_img_mgmt_active_slot) /*=0x2000ab7c*/;
    int iVar2;
    unsigned uVar4;
    int *piVar5;
    volatile int local_24;
    volatile uint8_t auStack_20[8];

    memset_bytes();
    if (P1(4) == -1) return 0x14;
    if (P1(4) != 0) {
        uVar4 = puVar1[2];
        P2u(0xc) = puVar1[0];
        P2u(0) = uVar4;
        P2u(4) = 0;
        if (P1(4) == (int)puVar1[1]) {
            if (uVar4 < (unsigned)(P1(4) + P1(0x10))) return 0x1f;
            P2u(8) = P1(0x10);
            *(volatile uint8_t*)((char*)param_2 + 0x10) = 1;
        }
        return 0;
    }
    if ((unsigned)P1(0x10) < 0x20) return 0x16;
    if (P1(8) == -1) return 0x15;
    P2u(0) = P1(8);
    P2u(4) = 0;
    piVar5 = (int*)(intptr_t)P1(0xc);
    if (*(volatile int*)piVar5 != (int)0x96f3b83d) return 0x17;
    uVar4 = P1(0x18);
    if (0x20 < uVar4) return 0x18;
    if (uVar4 != 0 && *puVar1 != 0xffffffff && uVar4 == (unsigned)*(volatile uint8_t*)((uintptr_t)&g_img_mgmt_flash_area_align) /*=0x2000ab88*/) {
        iVar2 = memcmp();
        if (iVar2 == 0) return 0;
    }
    iVar2 = P1(0);
    if (iVar2 == -1) iVar2 = 0;
    uVar4 = FUN_00080a46();
    if (3 < uVar4) {
        printk();
        printk();
        assert_post_action();
    }
    iVar2 = FUN_000809f6();
    if (iVar2 != 0) {
        P2u(0xc) = 0xffffffff;
        return 9;
    }
    uVar4 = FUN_0005169c();
    P2u(0xc) = uVar4;
    if ((int)uVar4 < 0) return 9;
    if (flash_area_open() != 0) {
        FUN_0008096a();
        return 10;
    }
    if (*(volatile uint32_t*)(local_24 + 8) < (unsigned)P1(8)) {
        nullsub_3();
        FUN_0008096a();
        return 0x1e;
    }
    nullsub_3();
    if ((int8_t)P1(0x1c) != 0) {
        iVar2 = FUN_00080a82();
        if (iVar2 != 0) return 0x1a;
        iVar2 = FUN_00080970();
        if (-1 < iVar2) return 0x1b;
    }
    P2u(8) = P1(0x10);
    *(volatile uint8_t*)((char*)param_2 + 0x10) = 1;
    return 0;
}

