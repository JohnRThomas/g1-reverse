/* readable reconstruction; identity: FUN_000370b0 @ 0x000370b0
 * public-name: FUN_000370b0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_dashboard_disp_mode                    @ 0x2000496a
 */
/* Reconstructed FUN_000370b0 @ 0x370b0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t FUN_000370b0(void) {
    return *(volatile uint8_t*)0x2000496aUL;
}
