/* readable reconstruction; identity: FUN_0102759e @ 0x0102759e
 * public-name: FUN_0102759e
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0102759e @ 0x0102759e, exact Thumb extent 0x34 bytes. */
#include <stdint.h>

extern void FUN_0102693a(void *record, uint16_t available_bytes,
                         uint16_t link_units, uint8_t packet_mode,
                         uint16_t item_count);
#define controller_packet_record_init FUN_0102693a

/* Typed entry for initializing the secondary packet record. */
void FUN_0102759e(void *record, uint16_t available_bytes,
                  uint16_t link_units, uint8_t packet_mode,
                  uint16_t item_count)
{
    volatile uint16_t narrowed_available = available_bytes;
    volatile uint16_t narrowed_link = link_units;
    volatile uint8_t narrowed_mode = packet_mode;
    volatile uint16_t narrowed_count = item_count;
    controller_packet_record_init(record, narrowed_available, narrowed_link,
                                  narrowed_mode, narrowed_count);
}
