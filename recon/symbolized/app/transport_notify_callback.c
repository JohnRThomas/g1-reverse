#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00084840 @ 0x00084840
 * public-name: transport_notify_callback
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   transport_notify_callback                <= FUN_00084840 @ 0x00084840
 */
/* Optional transport callback FUN_00084840 @ 0x84840 (14-byte extent). */
#include <stdint.h>
typedef int (*callback_t)(uint8_t *object, uint32_t event, uint32_t context);
int transport_notify_callback(uint8_t *object, uint32_t event)
{
    uint8_t *transport = *(uint8_t **)(*(uint8_t **)(object + 0x10) + 0x0c);
    callback_t callback = *(callback_t *)transport;
    if (callback != 0)
        return callback(object, event, *(uint32_t *)(transport + 4));
    return (int)(uintptr_t)object;
}
