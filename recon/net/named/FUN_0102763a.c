/* readable reconstruction; identity: FUN_0102763a @ 0x0102763a
 * public-name: FUN_0102763a
 * durable-map: recon/catalogs/function_names_net.json
 */
/* sdc_descriptor_type9_size @ 0x0102763a; raw FUN_0102763a
 * Private unpublished SDC-local identity; type 9 is proven by its caller.
 */
#include <stdint.h>

#define sdc_descriptor_type9_size FUN_0102763a

extern int FUN_01026a7e(uint16_t, uint8_t, uint16_t); /* sdc_descriptor_size */

int sdc_descriptor_type9_size(uint16_t first, uint8_t kind, uint16_t count)
{
    volatile uint16_t narrowed_first = first;
    volatile uint8_t narrowed_kind = kind;
    volatile uint16_t narrowed_count = count;

    return FUN_01026a7e(narrowed_first, narrowed_kind, narrowed_count);
}
