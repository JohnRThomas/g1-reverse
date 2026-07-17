/* readable reconstruction; identity: FUN_0100cbe4 @ 0x0100cbe4
 * public-name: controller_six_byte_record_store
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_six_byte_record_store         <= FUN_0100cbe4 @ 0x0100cbe4
 * address symbols (name @ address):
 *   g_net_radio_addr_match_tbl               @ 0x21000d18
 */
/* net-core controller_six_byte_record_store @ 0x0100cbe4.
 * Raw/address backmap: FUN_0100cbe4@0x0100cbe4. */
#include <stdint.h>
#define controller_six_byte_record_store controller_six_byte_record_store

void controller_six_byte_record_store(const void *record, uint32_t index)
{
    const uint8_t *source = (const uint8_t *)record;
    volatile uint8_t *destination =
        (volatile uint8_t *)(0x21000d18u + 0x10au + index * 6u);

    *(volatile uint32_t *)destination = *(const uint32_t *)source;
    *(volatile uint16_t *)(destination + 4) = *(const uint16_t *)(source + 4);
}
