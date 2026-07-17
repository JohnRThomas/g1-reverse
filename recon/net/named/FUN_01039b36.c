/* readable reconstruction; identity: FUN_01039b36 @ 0x01039b36
 * public-name: FUN_01039b36
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01039b36 @ 0x01039b36 */
#include <stdint.h>

typedef void (*dispatch_fn)(uint32_t, uint32_t, uint32_t, uint32_t);

extern dispatch_fn FUN_0102cb84(uint8_t *, uint32_t);

void FUN_01039b36(uint32_t context, uint32_t object, uint32_t kind,
                   uint32_t argument)
{
    dispatch_fn callback =
        FUN_0102cb84((uint8_t *)(uintptr_t)object + 4, argument);
    if (callback != 0) {
        callback(context, object, kind, argument);
    }
}
