#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00068280 @ 0x00068280
 * public-name: metal_generic_bus_deinit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   metal_generic_bus_deinit                 <= FUN_00068280 @ 0x00068280
 *   metal_generic_bus_unregister             <= FUN_000682a8 @ 0x000682a8
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_metal_generic_bus                      @ 0x2000b424
 */
/* Reconstructed FUN_00068280 @ 0x68280  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern void metal_generic_bus_unregister(void);
extern void memset_bytes(void *dst, int val, int len);

void metal_generic_bus_deinit(void)
{
    metal_generic_bus_unregister();
    memset_bytes((void *)((unsigned long)&g_metal_generic_bus) /*=0x2000b424*/, 0, 0x20);
}
