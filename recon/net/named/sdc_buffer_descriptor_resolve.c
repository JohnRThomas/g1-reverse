/* readable reconstruction; identity: FUN_0102714a @ 0x0102714a
 * public-name: sdc_buffer_descriptor_resolve
 * durable-map: recon/catalogs/function_names_net.json
 */
/* Reconstructed sdc_buffer_descriptor_resolve @ 0x0102714a.
 * Back-map: FUN_0102714a.  Exact extent: 76 bytes.
 */
#include <stdint.h>
uint16_t sdc_buffer_descriptor_resolve(const uint16_t *descriptor,
                                       void **payload,
                                       uint16_t *minimum_length)
{
    uint16_t length = descriptor[0];
    if (length < 0x45u) {
        length = 0x45u;
    }
    *minimum_length = length;
    *payload = (uint8_t *)descriptor + 0x18u + (descriptor[3] & 0x7fffu);
    return descriptor[6];
}
