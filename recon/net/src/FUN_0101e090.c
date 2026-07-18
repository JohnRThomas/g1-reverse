/* FUN_0101e090 @ 0x0101e090: resolve an inactive connection's typed handle. */
#include <stdint.h>

extern void *controller_typed_handle_lookup(uint32_t handle, uint32_t type);

void *sdc_connection_typed_handle_if_inactive(const uint8_t *connection)
{
    if (connection[0x1c2] != 0u) {
        return 0;
    }
    return controller_typed_handle_lookup(*(const uint16_t *)(connection + 0x17c), 1u);
}

/* Raw identity/back-map: FUN_0101e090 @ 0x0101e090, true extent 0x14. */
extern __typeof(sdc_connection_typed_handle_if_inactive) FUN_0101e090
    __attribute__((alias("sdc_connection_typed_handle_if_inactive")));
