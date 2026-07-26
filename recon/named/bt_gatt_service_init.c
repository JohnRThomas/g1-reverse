/* readable reconstruction; identity: FUN_00059cb4 @ 0x00059cb4
 * public-name: bt_gatt_service_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_gatt_service_init                     <= FUN_00059cb4 @ 0x00059cb4
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   atomic_or_0                              <= FUN_000826e0 @ 0x000826e0
 * address symbols (name @ address):
 *   rodata_88058                             @ 0x00088058
 *   rodata_88070                             @ 0x00088070
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0d20                             @ 0x000f0d20   [INLINED -- G6 literal batch]
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f49ac                             @ 0x000f49ac
 *   gatt_service_init_guard                  @ 0x2000af04
 *   last_static_handle                       @ 0x2000ff3c
 */
#include "../headers/g1_log.h"
/* Reconstructed FUN_00059cb4 @ 0x59cb4  (parity: 300/300 trials, PROVEN) */

extern unsigned long long atomic_or_0(int a, int b);
extern void assert_post_action(int a, int b);

void bt_gatt_service_init(void)
{
    unsigned long long uVar5;
    unsigned short sVar2;
    int bVar3;
    unsigned int uVar4;

    uVar5 = atomic_or_0(0x2000af04, 2);
    if (((unsigned int)uVar5 & (unsigned int)(uVar5 >> 32)) == 0) {
        sVar2 = *(volatile unsigned short *)0x2000ff3cUL;
        bVar3 = 0;
        uVar4 = 0x88058;
        while (1) {
            if (0x88070 < uVar4) {
                if (bVar3) {
                    *(volatile unsigned short *)0x2000ff3cUL = sVar2;
                }
                printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), 0xf49ac, 0xf46b8, 0x5ad);
                printk(((unsigned long)"\tunexpected list end location\n"), 0, 0, 0);
                assert_post_action(0xf46b8, 0x5ad);
            }
            if (0x88070 <= uVar4) break;
            sVar2 = (unsigned short)(sVar2 + *(int *)(uVar4 + 4));
            uVar4 = uVar4 + 8;
            bVar3 = 1;
        }
        if (bVar3) {
            *(volatile unsigned short *)0x2000ff3cUL = sVar2;
        }
    }
}
