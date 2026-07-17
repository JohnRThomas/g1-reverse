/* readable reconstruction; identity: FUN_0103a44c @ 0x0103a44c
 * public-name: FUN_0103a44c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103a44c @ 0x0103a44c */
#include <stdint.h>

extern uint32_t FUN_0102fdd0(uint32_t, uint32_t, uint32_t, uint32_t);

uint32_t FUN_0103a44c(uint32_t object, uint32_t unused, uint32_t arg2,
                      uint32_t arg3)
{
    uint32_t nested = *(uint32_t *)(uintptr_t)(object + 0x2c);
    (void)unused;
    nested = *(uint32_t *)(uintptr_t)(nested + 4);
    return FUN_0102fdd0(object, *(uint32_t *)(uintptr_t)nested, arg2, arg3);
}
