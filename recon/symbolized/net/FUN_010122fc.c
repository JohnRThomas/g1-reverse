#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010122fc @ 0x010122fc
 * public-name: FUN_010122fc
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core record submission wrapper FUN_010122fc @ 0x010122fc, 48 bytes. */
#include <stdint.h>

extern uint32_t FUN_01011d14(uint32_t value, const void *description);

struct record_description_122fc {
    uint8_t *payload;
    uint16_t flags;
    uint16_t reserved;
    uint32_t context;
    uint16_t type;
};

uint32_t FUN_010122fc(uint8_t *record, uint32_t value)
{
    uint16_t flags = *(uint16_t *)(record + 2);

    if ((flags & 0x18u) != 0)
        return 1;

    struct record_description_122fc description;
    uint8_t *payload = record + 0x28;
    uint32_t context = *(uint32_t *)(record + 8);
    uint16_t type = *(uint16_t *)(record + 4);
    description.payload = payload;
    description.flags = flags;
    description.context = context;
    description.type = type;
    return FUN_01011d14(value, &description);
}
