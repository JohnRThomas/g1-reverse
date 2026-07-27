#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005cac0 @ 0x0005cac0
 * public-name: conn_auth_cb_get_or_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   conn_auth_cb_get_or_init                 <= FUN_0005cac0 @ 0x0005cac0
 * address symbols (name @ address):
 *   g_bt_conn_auth_cb                        @ 0x2000ad28
 */
/* Reconstructed FUN_0005cac0 @ 0x5cac0, exact extent 34 bytes. */
#include <stdint.h>

int conn_auth_cb_get_or_init(unsigned long object) {
    volatile uintptr_t *slot = (volatile uintptr_t *)(object + 0x238u);
    uintptr_t expected = 0x20006450u;
    uintptr_t replacement = *(volatile uintptr_t *)((unsigned long)&g_bt_conn_auth_cb) /*=0x2000ad28*/;

    __atomic_compare_exchange_n(slot, &expected, replacement, 0,
                                __ATOMIC_RELAXED, __ATOMIC_RELAXED);
    return __atomic_load_n(slot, __ATOMIC_ACQUIRE);
}
