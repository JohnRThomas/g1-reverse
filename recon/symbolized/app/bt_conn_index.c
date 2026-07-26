#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000569a0 @ 0x000569a0
 * public-name: bt_conn_index
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_conn_index                            <= FUN_000569a0 @ 0x000569a0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3a5d                             @ 0x000f3a5d
 *   rodata_f3c92                             @ 0x000f3c92   [INLINED -- G6 literal batch]
 *   rodata_f3d5b                             @ 0x000f3d5b   [INLINED -- G6 literal batch]
 *   g_ble_conn_pool                          @ 0x20006138
 */
/* Reconstructed FUN_000569a0 @ 0x569a0  (parity: 300/300 trials, PROVEN) */

extern void assert_post_action(unsigned int, unsigned int);

unsigned int bt_conn_index(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int diff = param_1 - (int)((unsigned long)&g_ble_conn_pool) /*=0x20006138*/;
    int shifted = diff >> 3;
    unsigned int R = (0x684bda13U * (unsigned int)shifted) & 0xffU;
    if (param_1 != (int)((unsigned long)&g_ble_conn_pool) /*=0x20006138*/) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"index >= 0 && index < ((size_t) (((int) sizeof(char[1 - 2 * !(!__builtin_types_compatible_p(__typeof__(acl_conns), __typeof__(&(acl_conns)[0])))]) - 1) + (sizeof(acl_conns) / sizeof((acl_conns)[0]))))") /*=0xf3c92*/, ((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x543UL);
        printk(((unsigned long)"\tInvalid bt_conn pointer\n") /*=0xf3d5b*/, ((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x543UL, 0x543UL);
        assert_post_action(((unsigned long)&rodata_f3a5d) /*=0xf3a5d*/, 0x543UL);
        return 0x543U & 0xffU;
    }
    return R;
}
