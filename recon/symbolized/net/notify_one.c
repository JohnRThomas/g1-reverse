#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039b36 @ 0x01039b36
 * public-name: notify_one
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   notify_one                               <= FUN_01039b36 @ 0x01039b36
 */
/* net-core FUN_01039b36 @ 0x01039b36 */
#include <stdint.h>

typedef void (*dispatch_fn)(uint32_t, uint32_t, uint32_t, uint32_t);

extern dispatch_fn FUN_0102cb84(uint8_t *, uint32_t);

void notify_one(uint32_t context, uint32_t object, uint32_t kind,
                   uint32_t argument)
{
    dispatch_fn callback =
        FUN_0102cb84((uint8_t *)(uintptr_t)object + 4, argument);
    if (callback != 0) {
        callback(context, object, kind, argument);
    }
}
