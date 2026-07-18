/* sdc_descriptor_type5_size @ 0x01027742; raw FUN_01027742
 * Private unpublished SDC-local identity; type 5 is proven by its caller.
 */
#include <stdint.h>

#define sdc_descriptor_type5_size FUN_01027742

extern int FUN_01026a7e(uint16_t, uint8_t, uint16_t); /* sdc_descriptor_size */

int sdc_descriptor_type5_size(uint16_t first, uint8_t kind, uint16_t count)
{
    volatile uint16_t narrowed_first = first;
    volatile uint8_t narrowed_kind = kind;
    volatile uint16_t narrowed_count = count;

    return FUN_01026a7e(narrowed_first, narrowed_kind, narrowed_count);
}
