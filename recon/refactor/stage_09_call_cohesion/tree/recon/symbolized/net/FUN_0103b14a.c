#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103b14a @ 0x0103b14a
 * public-name: FUN_0103b14a
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103b14a @ 0x103b14a */
#include <stdint.h>
#include <cmsis_gcc.h>

uint32_t FUN_0103b14a(void)
{
    return __get_IPSR() != 0U;
}
