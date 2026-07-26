#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005833c @ 0x0005833c
 * public-name: att_chan_req_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   att_chan_req_free                        <= FUN_0005833c @ 0x0005833c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   net_pkt_skip                             <= FUN_00086502 @ 0x00086502
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f3b6f                             @ 0x000f3b6f
 *   rodata_f4388                             @ 0x000f4388
 *   rodata_f43b7                             @ 0x000f43b7   [INLINED -- G6 literal batch]
 *   rodata_f43b8                             @ 0x000f43b8
 *   g_bt_att_pool                            @ 0x20003a28
 *   g_bt_gatt_indicate_ctx_pool              @ 0x2000add4
 *   att_handle_rsp_thread                    @ 0x2000ae9c
 */
/* Reconstructed FUN_0005833c @ 0x5833c, exact extent 118 bytes. */
#include <stdint.h>
#include "../../headers/g1_log.h"

extern void assert_post_action(uintptr_t file, uint32_t line);
extern void net_pkt_skip(uintptr_t queue, void *item);
extern void memset_bytes(void *destination, uint32_t value, uint32_t length);

void att_chan_req_free(uint32_t *item)
{
    if (item == 0) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f3b6f) /*=0xf3b6f*/, ((unsigned long)&rodata_f4388) /*=0xf4388*/, 0xc4u);
        assert_post_action(((unsigned long)&rodata_f4388) /*=0xf4388*/, 0xc4u);
        return;
    }

    uint32_t *owner_item = (uint32_t *)(uintptr_t)(*item + 0x148u);
    uintptr_t address = (uintptr_t)item;
    if (address < ((unsigned long)&g_bt_gatt_indicate_ctx_pool) /*=0x2000add4*/ || address >= ((unsigned long)&att_handle_rsp_thread) /*=0x2000ae9c*/) {
        if (owner_item == item) {
            memset_bytes(item, 0u, 0x14u);
            return;
        }
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)&rodata_f43b8) /*=0xf43b8*/, ((unsigned long)&rodata_f4388) /*=0xf4388*/, 0xcdu);
        assert_post_action(((unsigned long)&rodata_f4388) /*=0xf4388*/, 0xcdu);
        return;
    }

    if (owner_item == item) {
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"!alloc_from_global") /*=0xf43b7*/, ((unsigned long)&rodata_f4388) /*=0xf4388*/, 0xcbu);
        assert_post_action(((unsigned long)&rodata_f4388) /*=0xf4388*/, 0xcbu);
        return;
    }

    memset_bytes(item, 0u, 0x14u);
    net_pkt_skip(((unsigned long)&g_bt_att_pool) /*=0x20003a28*/, item);
}
