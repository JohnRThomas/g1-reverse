/* readable reconstruction; identity: FUN_0103a9be @ 0x0103a9be
 * public-name: FUN_0103a9be
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103a9be @ 0x0103a9be */
#include <stdint.h>

extern void FUN_0103a924(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                         const uint8_t *);

void FUN_0103a9be(uint32_t object, uint8_t value)
{
    uint8_t local = value;
    FUN_0103a924(object, 0, 0, 0, 0, &local);
}
