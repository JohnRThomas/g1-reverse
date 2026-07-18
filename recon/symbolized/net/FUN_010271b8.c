#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010271b8 @ 0x010271b8
 * public-name: FUN_010271b8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* sdc_free_block_insert @ 0x010271b8; raw FUN_010271b8
 * Private unpublished SDC-local identity; readable name describes behavior.
 */

#define sdc_free_block_insert FUN_010271b8

struct sdc_free_block {
    struct sdc_free_block *next;
    unsigned short size;
};

void sdc_free_block_insert(struct sdc_free_block *block,
                           struct sdc_free_block **link)
{
    block->next = *link;
    *link = block;
}
