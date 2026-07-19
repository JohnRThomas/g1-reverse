/* readable reconstruction; identity: FUN_000543c8 @ 0x000543c8
 * public-name: bt_hci_driver_send
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_hci_driver_send                       <= FUN_000543c8 @ 0x000543c8
 * address symbols (name @ address):
 *   g_20002168                               @ 0x20002168
 */
/* Reconstructed FUN_000543c8 @ 0x543c8, exact extent 10 bytes. */
#include <stdint.h>

typedef uint32_t (*dispatch_fn_t)(void);

uint32_t bt_hci_driver_send(void)
{
    uintptr_t object = *(volatile uintptr_t *)0x20002168u;
    dispatch_fn_t dispatch = *(dispatch_fn_t volatile *)(object + 0x14u);
    return dispatch();
}
