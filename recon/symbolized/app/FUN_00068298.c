#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00068298 @ 0x00068298
 * public-name: FUN_00068298
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_module_registry_node                   @ 0x20002c3c
 */
/* Reconstructed FUN_00068298 @ 0x68298
 * CFG_VERIFY_CALL_ARITIES=1
 * Readable identity: metal_sys_init (libmetal Zephyr system backend).
 * Raw/address backmap: metal_sys_init <= FUN_00068298 @ 0x00068298.
 */

#include <stdint.h>

extern int FUN_00068170(void *bus); /* metal_bus_register */

int FUN_00068298(const void *params)
{
    (void)params;
    (void)FUN_00068170((void *)((unsigned long)&g_module_registry_node) /*=0x20002c3c*/);
    return 0;
}
