#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010271da @ 0x010271da
 * public-name: FUN_010271da
 * durable-map: recon/catalogs/function_names_net.json
 */
/* sdc_free_list_advance @ 0x010271da; raw FUN_010271da.
 * Private controller identity; true executable extent 0x1c bytes.
 */
#include <stdint.h>
struct sdc_free_block { struct sdc_free_block *next; uint16_t size; };
void FUN_010271da(struct sdc_free_block **link)
{
    *link = (*link)->next;
}
/* Raw identity/back-map: FUN_010271da@0x010271da. */
