/* readable reconstruction; identity: FUN_000370b0 @ 0x000370b0
 * public-name: get_dashboard_disp_mode
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_dashboard_disp_mode                  <= FUN_000370b0 @ 0x000370b0
 * address symbols (name @ address):
 *   g_dashboard_disp_mode                    @ 0x2000496a
 */
/* Reconstructed FUN_000370b0 @ 0x370b0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
uint8_t get_dashboard_disp_mode(void) {
    return *(volatile uint8_t*)0x2000496aUL;
}
