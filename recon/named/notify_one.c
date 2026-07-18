/* readable reconstruction; identity: FUN_0007e1e6 @ 0x0007e1e6
 * public-name: notify_one
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed notify_one @ 0x7e1e6  (CFG-directed candidate) */
/* Owner: Zephyr 3.4.99 lib/os/onoff.c; raw backmap FUN_0007e1e6@0x0007e1e6.
 * CFG_VERIFY_ORACLE0_R0_POINTER exercises the non-null callback path. */
#include <stdint.h>
typedef void (*onoff_client_callback)(void *manager, void *client, uint32_t state, int32_t result);
extern uintptr_t FUN_0004bb0c(void *notify, int32_t result);
void notify_one(void *manager, void *client, uint32_t state, int32_t result)
{
    onoff_client_callback callback = (onoff_client_callback)FUN_0004bb0c((uint8_t *)client + 4u, result);
    if (callback != 0) {
        callback(manager, client, state, result);
    }
}
