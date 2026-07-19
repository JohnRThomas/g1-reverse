/* readable reconstruction; identity: FUN_0007c85e @ 0x0007c85e
 * public-name: ipc_transport_ops_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_transport_ops_dispatch               <= FUN_0007c85e @ 0x0007c85e
 */
/* Full reconstruction FUN_0007c85e @ 0x7c85e (exact extent 14 bytes). */
#include <stdint.h>
typedef int (*transfer_callback_t)(uint8_t *, void *, uint32_t, uint32_t);

int ipc_transport_ops_dispatch(uint8_t *object, void *parts, uint32_t count, uint32_t operation)
{
    uint8_t *vtable = *(uint8_t **)(object + 8);
    transfer_callback_t callback = *(transfer_callback_t *)(vtable + 8);
    return callback(object, parts, count, operation);
}
