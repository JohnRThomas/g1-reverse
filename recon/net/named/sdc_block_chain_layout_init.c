/* readable reconstruction; identity: FUN_010279e6 @ 0x010279e6
 * public-name: sdc_block_chain_layout_init
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_block_chain_layout_init              <= FUN_010279e6 @ 0x010279e6
 */
/* net-core FUN_010279e6 @ 0x010279e6 */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t, uint32_t);
extern uint32_t FUN_01027974(uint32_t *, uint32_t, uint32_t, uint32_t);

uint32_t sdc_block_chain_layout_init(uint32_t *header, uint16_t type, uint16_t payload_size)
{
    volatile uint16_t saved_type = type;
    volatile uint16_t saved_payload_size = payload_size;
    volatile uint32_t allocation_size =
        ((uint32_t)saved_payload_size + 7u & ~7u) + 0x10u;
    uint32_t result;

    if (((uintptr_t)header & 7u) != 0u) {
        sdc_assertion_fail(0x22u, 0x66u);
    }
    if (header != 0) {
        header[0] = (uint32_t)(uintptr_t)(header + 2);
        *(uint16_t *)(header + 1) = saved_type;
        *(uint16_t *)((uint8_t *)header + 6) = saved_payload_size;
    }
    result = FUN_01027974(header, 8u, saved_type, allocation_size);
    __asm__ volatile ("" ::: "memory");
    return result;
}
