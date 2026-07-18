/* readable reconstruction; identity: FUN_01027044 @ 0x01027044
 * public-name: FUN_01027044
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET private payload locator @ 0x01027044.
 * Raw back-map: FUN_01027044@0x01027044; extent 0x5a. */
#include <stdint.h>

extern int FUN_01026912(uint16_t encoded_length, uint16_t type);

void *FUN_01027044(uint8_t *record)
{
    uint16_t encoded = *(uint16_t *)(record + 4);
    uint8_t *payload = record + 0x18 + (encoded & 0x7fffu);
    if (FUN_01026912(encoded, *(uint16_t *)(record + 6)) != 0)
        return 0;
    if (*(uint16_t *)(record + 0x0a) != 0)
        return 0;
    return payload;
}
