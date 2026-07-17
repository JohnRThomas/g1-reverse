#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010270d2 @ 0x010270d2
 * public-name: sdc_buffer_payload_get
 * durable-map: recon/catalogs/function_names_net.json
 */
/* Reconstructed sdc_buffer_payload_get @ 0x010270d2.
 * Back-map: FUN_010270d2.  Exact extent: 22 bytes.
 */
#include <stdint.h>
void *sdc_buffer_payload_get(void *handle)
{
    return (uint8_t *)handle + 2;
}
