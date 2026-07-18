/* readable reconstruction; identity: FUN_010126c8 @ 0x010126c8
 * public-name: FUN_010126c8
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_010126c8 @ 0x10126c8  (CFG-directed candidate) */

#include <stdint.h>
extern uint32_t FUN_01028010(uint32_t);
uint32_t FUN_010126c8(uint8_t *connection)
{
    uint16_t flags = *(uint16_t *)(connection + 2);
    uint32_t selected = (flags & 0x10u) ? 1u : ((flags >> 1) & 1u);
    return (FUN_01028010(*(uint32_t *)(connection + 0x44)) | selected) & 0xffu;
}
