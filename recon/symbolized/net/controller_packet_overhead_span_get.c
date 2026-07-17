#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01026856 @ 0x01026856
 * public-name: controller_packet_overhead_span_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_overhead_span_get      <= FUN_01026856 @ 0x01026856
 */
/* net-core FUN_01026856 @ 0x01026856, exact Thumb extent 0x1c bytes. */
#include <stdint.h>

/* Encoded packet-mode byte to header/trailer span. */
uint16_t controller_packet_overhead_span_get(uint8_t packet_mode)
{
    /* The firmware truncates r0 at entry; callers need not canonicalize the
     * unused upper AAPCS bits of this narrow argument. */
    volatile uint8_t stored_mode = packet_mode;
    return (uint16_t)stored_mode + 5u;
}
