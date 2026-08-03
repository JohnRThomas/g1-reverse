#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01027196 @ 0x01027196
 * public-name: FUN_01027196
 * durable-map: recon/catalogs/function_names_net.json
 */
/* sdc_free_block_init @ 0x01027196; raw FUN_01027196
 * Private unpublished SDC-local identity; readable name describes behavior.
 */
#include <stdint.h>

#define sdc_free_block_init FUN_01027196

struct sdc_free_block {
    struct sdc_free_block *next;
    uint16_t size;
};

void sdc_free_block_init(struct sdc_free_block *block, uint16_t size)
{
    *(struct sdc_free_block * volatile *)&block->next = 0;
    *(volatile uint16_t *)&block->size = size;
}
