#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e5dc @ 0x0100e5dc
 * public-name: sdc_pdu_type_bits_set
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_pdu_type_bits_set                    <= FUN_0100e5dc @ 0x0100e5dc
 */
/* net-core FUN_0100e5dc @ 0x100e5dc  (CFG-directed candidate) */
#include <stdint.h>

/* Raw back-map: FUN_0100e5dc @ 0x0100e5dc, exact extent 0x10 bytes. */
void sdc_pdu_type_bits_set(uint8_t *header, uint32_t type)
{
    *header = (uint8_t)((*header & 0xfcu) | (type & 3u));
}
