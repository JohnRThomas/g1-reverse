#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100e038 @ 0x0100e038
 * public-name: FUN_0100e038
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0100e038 @ 0x100e038  (CFG-directed candidate) */
void FUN_0100e038(unsigned char *p, unsigned int value)
{
    *p = (unsigned char)((*p & 0xbfu) | ((value << 6) & 0x40u));
}
