#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004f500 @ 0x0004f500
 * public-name: FUN_0004f500
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_2000a2b8                               @ 0x2000a2b8
 */
/* Reconstructed FUN_0004f500 @ 0x4f500
 * Readable identity: ANCS GATT client callback configuration setter.
 * Raw/address backmap: FUN_0004f500 @ 0x0004f500.
 */

#include <stdint.h>

int FUN_0004f500(const uint32_t *configuration)
{
    volatile uint32_t *const active_configuration =
        (volatile uint32_t *)((unsigned long)&g_2000a2b8) /*=0x2000a2b8*/;

    if (configuration != 0) {
        active_configuration[0] = configuration[0];
        active_configuration[1] = configuration[1];
        active_configuration[2] = configuration[2];
    }
    return 0;
}
