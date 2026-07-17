/* readable reconstruction; identity: FUN_01010110 @ 0x01010110
 * public-name: FUN_01010110
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01010110 @ 0x01010110 */
#include <stdint.h>

/* Raw/address backmap: controller_mask_read = FUN_0101f8cc@0x0101f8cc. */
extern uint64_t FUN_0101f8cc(const void *controller);

void FUN_01010110(const uint8_t *controller, uint32_t *destination)
{
    const uint8_t *radio = *(const uint8_t * const *)(controller + 4);
    uint64_t masks = FUN_0101f8cc(controller);
    uint32_t low_mask = (uint32_t)masks & 0xf704492fu;
    uint32_t high_mask = (uint32_t)(masks >> 32) & 0x1807u;

    low_mask = (low_mask & ~0xffu) | ((uint32_t)radio[0x116] & low_mask);
    destination[1] = low_mask;
    destination[2] = high_mask;
}
