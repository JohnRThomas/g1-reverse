#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005e758 @ 0x0005e758
 * public-name: bt_keys_foreach_type
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_keys_foreach_type                     <= FUN_0005e758 @ 0x0005e758
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f5268                             @ 0x000f5268
 *   rodata_f52c0                             @ 0x000f52c0
 *   bt_keys_pool                             @ 0x2000af4c
 *   bt_keys_pool_1                           @ 0x2000afa8
 */
/* Reconstructed FUN_0005e758 @ 0x5e758  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
typedef void (*fnptr)(unsigned int, unsigned int);
extern void assert_post_action(uint32_t, uint32_t);

void bt_keys_foreach_type(unsigned short param_1, fnptr param_2, unsigned int param_3)
{
    if (param_2 == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f52c0) /*=0xf52c0*/, ((unsigned long)&rodata_f5268) /*=0xf5268*/, 0xb3U);
        assert_post_action(((unsigned long)&rodata_f5268) /*=0xf5268*/, 0xb3U);
        return;
    }
    uintptr_t base = ((unsigned long)&bt_keys_pool) /*=0x2000af4c*/;
    unsigned short m1 = *(volatile unsigned short*)(base + 0xe);
    if ((m1 & param_1) != 0) {
        param_2((unsigned int)base, param_3);
    }
    unsigned short m2 = *(volatile unsigned short*)(base + 0x6a);
    if ((m2 & param_1) != 0) {
        param_2(((unsigned long)&bt_keys_pool_1) /*=0x2000afa8*/, param_3);
        return;
    }
}
