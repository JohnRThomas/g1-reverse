/* readable reconstruction; identity: FUN_0102d5b4 @ 0x0102d5b4
 * public-name: ipc_service_register_endpoint
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   ipc_service_register_endpoint            <= FUN_0102d5b4 @ 0x0102d5b4
 */
/* net-core FUN_0102d5b4 @ 0x0102d5b4 */
#include <stdint.h>

typedef int32_t (*transport_open_fn)(uint32_t, uint32_t *);

extern void FUN_01039e52(uint32_t, uint32_t, const uint32_t *);

int32_t ipc_service_register_endpoint(uint32_t instance, uint32_t *result, uint32_t endpoint)
{
    uint32_t log_args[2];
    uint32_t transport;
    transport_open_fn open_fn;

    if (instance == 0u || result == 0 || endpoint == 0u) {
        log_args[0] = 2u;
        log_args[1] = 0x0103d55bu;
        FUN_01039e52(0x0103c074u, 0x1040u, log_args);
        return -22;
    }

    transport = *(uint32_t *)(uintptr_t)(instance + 8u);
    if (transport == 0u ||
        (open_fn = *(transport_open_fn *)(uintptr_t)(transport + 0xcu)) == 0) {
        log_args[0] = 2u;
        log_args[1] = 0x0103d53du;
        FUN_01039e52(0x0103c074u, 0x1040u, log_args);
        return -5;
    }

    *result++ = instance;
    return open_fn(instance, result);
}
