/* readable reconstruction; identity: FUN_000682a8 @ 0x000682a8
 * public-name: metal_generic_bus_unregister
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   metal_bus_unregister                     <= FUN_000680f8 @ 0x000680f8
 *   metal_generic_bus_unregister             <= FUN_000682a8 @ 0x000682a8
 * address symbols (name @ address):
 *   g_module_registry_node                   @ 0x20002c3c
 */
/* Reconstructed FUN_000682a8 @ 0x682a8  (parity: 300/300 trials, PROVEN) */

extern unsigned int metal_bus_unregister(unsigned int a);

unsigned int metal_generic_bus_unregister(void)
{
    return metal_bus_unregister(0x20002c3cUL);
}
