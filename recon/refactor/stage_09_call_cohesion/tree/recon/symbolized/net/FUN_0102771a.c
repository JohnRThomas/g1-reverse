#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102771a @ 0x0102771a
 * public-name: FUN_0102771a
 * durable-map: recon/catalogs/function_names_net.json
 */
/* sdc_descriptor_type10_size @ 0x0102771a; raw FUN_0102771a
 * Private unpublished SDC-local identity; type 10 is proven by its caller.
 */
#include <stdint.h>

#define sdc_descriptor_type10_size FUN_0102771a

extern int FUN_01026a7e(uint16_t, uint8_t, uint16_t); /* sdc_descriptor_size */

int sdc_descriptor_type10_size(uint16_t first, uint8_t kind, uint16_t count)
{
    volatile uint16_t narrowed_first = first;
    volatile uint8_t narrowed_kind = kind;
    volatile uint16_t narrowed_count = count;

    return FUN_01026a7e(narrowed_first, narrowed_kind, narrowed_count);
}
