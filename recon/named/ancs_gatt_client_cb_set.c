/* readable reconstruction; identity: FUN_0004f500 @ 0x0004f500
 * public-name: ancs_gatt_client_cb_set
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_gatt_client_cb_set                  <= FUN_0004f500 @ 0x0004f500
 * address symbols (name @ address):
 *   g_2000a2b8                               @ 0x2000a2b8
 */
/* Reconstructed FUN_0004f500 @ 0x4f500
 * Readable identity: ANCS GATT client callback configuration setter.
 * Raw/address backmap: FUN_0004f500 @ 0x0004f500.
 */

#include <stdint.h>

int ancs_gatt_client_cb_set(const uint32_t *configuration)
{
    volatile uint32_t *const active_configuration =
        (volatile uint32_t *)0x2000a2b8UL;

    if (configuration != 0) {
        active_configuration[0] = configuration[0];
        active_configuration[1] = configuration[1];
        active_configuration[2] = configuration[2];
    }
    return 0;
}
