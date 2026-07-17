#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027790 @ 0x01027790
 * public-name: sdc_buffer_data_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_buffer_data_get                      <= FUN_01027790 @ 0x01027790
 */
/* net-core FUN_01027790 @ 0x01027790 */
#include <stdint.h>

void *sdc_buffer_data_get(void *controller_buffer)
{
    return (uint8_t *)controller_buffer + 4;
}
