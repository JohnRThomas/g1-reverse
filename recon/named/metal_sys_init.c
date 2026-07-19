/* readable reconstruction; identity: FUN_00068298 @ 0x00068298
 * public-name: metal_sys_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   metal_register_generic_device            <= FUN_00068170 @ 0x00068170
 *   metal_sys_init                           <= FUN_00068298 @ 0x00068298
 * address symbols (name @ address):
 *   g_module_registry_node                   @ 0x20002c3c
 */
/* Reconstructed FUN_00068298 @ 0x68298
 * CFG_VERIFY_CALL_ARITIES=1
 * Readable identity: metal_sys_init (libmetal Zephyr system backend).
 * Raw/address backmap: metal_sys_init <= FUN_00068298 @ 0x00068298.
 */

#include <stdint.h>

extern int metal_register_generic_device(void *bus); /* metal_bus_register */

int metal_sys_init(const void *params)
{
    (void)params;
    (void)metal_register_generic_device((void *)0x20002c3cUL);
    return 0;
}
