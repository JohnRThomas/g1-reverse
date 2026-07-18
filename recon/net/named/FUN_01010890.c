/* readable reconstruction; identity: FUN_01010890 @ 0x01010890
 * public-name: FUN_01010890
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01010890 @ 0x1010890  (CFG-directed candidate) */
/* CPUNET 0x01010890, true executable extent 0x28. Raw backmap: FUN_01010890. */
#include <stdint.h>

extern void FUN_010106dc(uint32_t handle, uint32_t flags, uint8_t *result);

void FUN_01010890(uint32_t mode, const uint8_t *request)
{
    uint8_t result;
    uint32_t flags = (uint32_t)request[4] | ((uint32_t)request[5] << 8);

    if (mode == 1u) {
        flags |= 0x10000u;
    }
    FUN_010106dc(*(const uint32_t *)request, flags, &result);
}
