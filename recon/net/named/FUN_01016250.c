/* readable reconstruction; identity: FUN_01016250 @ 0x01016250
 * public-name: FUN_01016250
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01016250 @ 0x01016250
 * Readable identity: controller_phy_uses_coded_timing.
 * Raw callee backmap: FUN_01008d00=sdc_assertion_fail.
 */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t file_id, uint32_t line_id)
    __attribute__((noreturn));

uint32_t FUN_01016250(uint32_t phy)
{
    switch (phy) {
    case 0u:
    case 2u:
        return 1u;
    case 1u:
    case 3u:
        return 0u;
    default:
        sdc_assertion_fail(0x77u, 0x225u);
    }
}
