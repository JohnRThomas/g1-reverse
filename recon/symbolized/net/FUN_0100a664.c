#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a664 @ 0x0100a664
 * public-name: FUN_0100a664
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_block_chain_layout_init              <= FUN_010279e6 @ 0x010279e6
 * address symbols (name @ address):
 *   g_net_pool_blk_cnt                       @ 0x21000bec
 *   g_net_pool_blk_size                      @ 0x21000bf0
 */
/* net-core FUN_0100a664 @ 0x100a664 */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t, uint32_t);
extern int32_t sdc_block_chain_layout_init(uint32_t, uint32_t, uint32_t);
extern uint32_t FUN_01027258(uint32_t *, uint32_t);

uint32_t FUN_0100a664(uint32_t raw_id, uint32_t raw_count,
                      uint32_t value, uint32_t raw_mode)
{
    uint32_t id = (uint32_t)raw_id & 0xffu;
    uint32_t count = (uint32_t)raw_count & 0xffu;
    uint32_t mode = (uint32_t)raw_mode & 0xffu;

    if ((value & 7u) == 0 || (value & 3u) != 0) {
        sdc_assertion_fail(0x4cu, 0x1fu);
    }

    int32_t scale = sdc_block_chain_layout_init(0, id, 0x10eu);
    uint32_t *value_pointer = mode == 0 ? &value : (uint32_t *)0;
    uint32_t result = FUN_01027258(value_pointer, (uint32_t)scale * count);

    if (mode != 1u) {
        *(volatile uint32_t *)((unsigned long)&g_net_pool_blk_cnt) /*=0x21000bec*/ = value;
        *(volatile int32_t *)((unsigned long)&g_net_pool_blk_size) /*=0x21000bf0*/ = scale;
    }
    return result;
}
