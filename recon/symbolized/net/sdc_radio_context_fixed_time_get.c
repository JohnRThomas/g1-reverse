#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100f0fc @ 0x0100f0fc
 * public-name: sdc_radio_context_fixed_time_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_radio_context_fixed_time_get         <= FUN_0100f0fc @ 0x0100f0fc
 */
/* net-core FUN_0100f0fc @ 0x0100f0fc */
#include <stdint.h>
uint32_t sdc_radio_context_fixed_time_get(const uint32_t *p){return p[1];}
