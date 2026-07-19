### FUN_0005cac0  @ 0x0005cac0  (size=34)

callers (5): smp_auth_get_pairing_method, FUN_0005cff0, FUN_0005d5c0, FUN_0005d964, FUN_0005e130
callees (0): (none)

```c
/* readable reconstruction; identity: FUN_0005cac0 @ 0x0005cac0
 * public-name: FUN_0005cac0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_bt_conn_auth_cb                        @ 0x2000ad28
 */
/* Reconstructed FUN_0005cac0 @ 0x5cac0, exact extent 34 bytes. */
#include <stdint.h>

uintptr_t FUN_0005cac0(uintptr_t object)
{
    volatile uintptr_t *slot = (volatile uintptr_t *)(object + 0x238u);
    uintptr_t expected = 0x20006450u;
    uintptr_t replacement = *(volatile uintptr_t *)0x2000ad28u;

    __atomic_compare_exchange_n(slot, &expected, replacement, 0,
                                __ATOMIC_RELAXED, __ATOMIC_RELAXED);
    return __atomic_load_n(slot, __ATOMIC_ACQUIRE);
}
```