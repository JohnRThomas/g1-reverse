/* readable reconstruction; identity: FUN_01024678 @ 0x01024678
 * public-name: sdc_timing_scale
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_timing_scale                         <= FUN_01024678 @ 0x01024678
 */
/* net-core FUN_01024678 @ 0x1024678 */
#include <stdint.h>

extern void FUN_010256dc(int subsystem, int reason, ...);

uint32_t sdc_timing_scale(uint32_t value, uint32_t scale,
                      uint32_t unused, uint32_t context)
{
    uint64_t product;
    uint32_t high;
    uint32_t quotient;
    uint32_t combined;

    (void)unused;
    if (scale == 0)
        return 0;
    if (value == 0)
        return 0;

    product = (uint64_t)value * scale - 1;
    high = (uint32_t)(product >> 32);
    if (high > 0x000f423f)
        FUN_010256dc(0x6d, 0x71, high, (uint32_t)product, context);

    high = (uint32_t)((product << 12) >> 32);
    quotient = high / 0xf424;
    combined = ((uint32_t)(product << 12) >> 16) + (high << 16);
    combined -= 0xf4240000u * quotient;
    return ((combined / 0xf424) | (quotient << 16)) + 1;
}
