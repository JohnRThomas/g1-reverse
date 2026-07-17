#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000518a8 @ 0x000518a8
 * public-name: img_mgmt_impl_write_image_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   flash_area_open                          <= FUN_0004e048 @ 0x0004e048
 *   img_mgmt_impl_write_image_data           <= FUN_000518a8 @ 0x000518a8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   nullsub_3                                <= FUN_0007ef7e @ 0x0007ef7e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_88208                             @ 0x00088208
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f2561                             @ 0x000f2561
 *   rodata_f25c5                             @ 0x000f25c5
 *   rodata_f25e2                             @ 0x000f25e2
 *   rodata_f25fb                             @ 0x000f25fb
 *   rodata_f26e7                             @ 0x000f26e7
 *   g_img_mgmt_active_slot                   @ 0x2000ab7c
 *   g_img_mgmt_flash_area_align              @ 0x2000ab88
 */
/* Reconstructed FUN_000518a8 @ 0x518a8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int flash_area_open(unsigned, void **);
extern unsigned FUN_0005169c(unsigned);
extern void assert_post_action(uint32_t, uint32_t);
extern void printk();
extern void nullsub_3(void);
extern void FUN_0008096a(uint32_t, uint32_t, const void *);
extern int FUN_00080970(void *, void *);
extern unsigned FUN_000809f6(unsigned);
extern unsigned FUN_00080a46(int);
extern int FUN_00080a82(void *);
extern int FUN_00086be4(void *, int);
extern void memset_bytes(void *, int, unsigned);

#define P1(k) (*(volatile int*)((char*)param_1 + (k)))
#define P2u(k) (*(volatile uint32_t*)((char*)param_2 + (k)))

unsigned img_mgmt_impl_write_image_data(int *param_1, unsigned *param_2)
{
    volatile uint32_t *puVar1 = (volatile uint32_t*)((unsigned long)&g_img_mgmt_active_slot) /*=0x2000ab7c*/;
    int iVar2;
    unsigned uVar4;
    int *piVar5;
    void *storage;
    uint8_t authorization[8];
    struct diagnostic_record {
        uint32_t severity;
        uint32_t message;
        uint32_t argument;
        uint32_t status;
    } diagnostic;

    memset_bytes(param_2, 0, 0x18);
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
    if (uVar4 != 0 && *puVar1 != 0xffffffff && uVar4 == (unsigned)*(volatile uint8_t*)((unsigned long)&g_img_mgmt_flash_area_align) /*=0x2000ab88*/) {
        iVar2 = FUN_00086be4((uint8_t *)puVar1 + 0xd, P1(0x14));
        if (iVar2 == 0) return 0;
    }
    iVar2 = P1(0);
    if (iVar2 == -1) iVar2 = 0;
    uVar4 = FUN_00080a46(iVar2);
    if (3 < uVar4) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f25c5) /*=0xf25c5*/, ((unsigned long)&rodata_f2561) /*=0xf2561*/, 0x71);
        printk(((unsigned long)&rodata_f25e2) /*=0xf25e2*/);
        assert_post_action(((unsigned long)&rodata_f2561) /*=0xf2561*/, 0x71);
    }
    uVar4 ^= 1;
    iVar2 = FUN_000809f6(uVar4);
    if (iVar2 != 0) {
        P2u(0xc) = 0xffffffff;
        return 9;
    }
    uVar4 = FUN_0005169c(uVar4);
    P2u(0xc) = uVar4;
    if ((int)uVar4 < 0) return 9;
    iVar2 = flash_area_open(uVar4 & 0xff, &storage);
    if (iVar2 != 0) {
        diagnostic.severity = 4;
        diagnostic.message = ((unsigned long)&rodata_f25fb) /*=0xf25fb*/;
        diagnostic.argument = P2u(0xc);
        diagnostic.status = (uint32_t)iVar2;
        FUN_0008096a(((unsigned long)&rodata_88208) /*=0x88208*/, 0x2040, &diagnostic);
        return 10;
    }
    if (*(volatile uint32_t *)((uint8_t *)storage + 8) < (unsigned)P1(8)) {
        nullsub_3();
        diagnostic.severity = 4;
        diagnostic.message = ((unsigned long)&rodata_f26e7) /*=0xf26e7*/;
        diagnostic.argument = P1(8);
        diagnostic.status = *(volatile uint32_t *)((uint8_t *)storage + 8);
        FUN_0008096a(((unsigned long)&rodata_88208) /*=0x88208*/, 0x2040, &diagnostic);
        return 0x1e;
    }
    nullsub_3();
    if ((int8_t)P1(0x1c) != 0) {
        iVar2 = FUN_00080a82(authorization);
        if (iVar2 != 0) return 0x1a;
        iVar2 = FUN_00080970(authorization, piVar5 + 5);
        if (-1 < iVar2) return 0x1b;
    }
    P2u(8) = P1(0x10);
    *(volatile uint8_t*)((char*)param_2 + 0x10) = 1;
    return 0;
}
