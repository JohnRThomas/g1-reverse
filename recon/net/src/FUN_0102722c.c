/* sdc_free_block_can_split @ 0x0102722c; raw FUN_0102722c.
 * Private controller identity; true executable extent 0x2c bytes.
 */
#include <stdint.h>
struct sdc_free_block { struct sdc_free_block *next; uint16_t size; };
uint8_t sdc_free_block_can_split(const struct sdc_free_block *block,
                                 uint16_t payload_size)
{
    uint16_t required = (uint16_t)(payload_size + 8u);
    return (uint8_t)(required <= block->size);
}
/* Raw identity/back-map: FUN_0102722c@0x0102722c. */
extern __typeof(sdc_free_block_can_split) FUN_0102722c
    __attribute__((alias("sdc_free_block_can_split")));
