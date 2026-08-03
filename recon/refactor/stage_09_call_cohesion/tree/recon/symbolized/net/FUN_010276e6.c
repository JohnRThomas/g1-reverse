#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010276e6 @ 0x010276e6
 * public-name: FUN_010276e6
 * durable-map: recon/catalogs/function_names_net.json
 */
/* sdc_descriptor_init @ 0x010276e6; raw FUN_010276e6
 * Private unpublished SDC-local identity; readable name describes behavior.
 */
#include <stdint.h>

#define sdc_descriptor_init FUN_010276e6

extern void FUN_0102693a(void *, uint16_t, uint16_t, uint8_t,
                         uint16_t); /* sdc_descriptor_initialize */

void sdc_descriptor_init(void *descriptor, uint16_t size, uint16_t first,
                         uint8_t kind, uint16_t count)
{
    volatile uint16_t narrowed_size = size;
    volatile uint16_t narrowed_first = first;
    volatile uint8_t narrowed_kind = kind;
    volatile uint16_t narrowed_count = count;

    FUN_0102693a(descriptor, narrowed_size, narrowed_first, narrowed_kind,
                  narrowed_count);
}
