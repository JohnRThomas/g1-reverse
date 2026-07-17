/* net-core FUN_01027662 @ 0x01027662, exact Thumb extent 0x28 bytes. */
#include <stdint.h>

extern uint16_t FUN_01026a7e(uint16_t link_units, uint8_t packet_mode,
                             uint16_t item_count);
#define controller_packet_record_storage_span_get FUN_01026a7e

/* Typed entry for computing the storage span required by a packet record. */
uint16_t FUN_01027662(uint16_t link_units, uint8_t packet_mode,
                      uint16_t item_count)
{
    volatile uint16_t narrowed_link = link_units;
    volatile uint8_t narrowed_mode = packet_mode;
    volatile uint16_t narrowed_count = item_count;
    return controller_packet_record_storage_span_get(narrowed_link,
                                                     narrowed_mode,
                                                     narrowed_count);
}
