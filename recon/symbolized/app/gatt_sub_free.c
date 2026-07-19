#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00059e78 @ 0x00059e78
 * public-name: gatt_sub_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gatt_sub_free                            <= FUN_00059e78 @ 0x00059e78
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   rodata_f46b8                             @ 0x000f46b8
 *   rodata_f4707                             @ 0x000f4707
 */
/* Reconstructed FUN_00059e78 @ 0x59e78  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int a, unsigned int b);
extern void printk(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void bt_addr_le_copy_828da(void *a, unsigned int b, unsigned int c, unsigned int d);

void gatt_sub_free(char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (*(volatile int*)(param_1 + 8) != 0) {
        printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f4707) /*=0xf4707*/, ((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0xd5c);
        assert_post_action(((unsigned long)&rodata_f46b8) /*=0xf46b8*/, 0xd5c);
    }
    bt_addr_le_copy_828da(param_1 + 1, ((unsigned long)&rodata_f2b3a) /*=0xf2b3a*/, param_3, param_4);
}
