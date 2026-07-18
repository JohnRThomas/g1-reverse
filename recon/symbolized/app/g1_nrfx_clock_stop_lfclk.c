#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00083880 @ 0x00083880
 * public-name: g1_nrfx_clock_stop_lfclk
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_nrfx_clock_stop_checked               <= FUN_00065324 @ 0x00065324
 *   g1_nrfx_clock_stop_lfclk                 <= FUN_00083880 @ 0x00083880
 */
/* Reconstructed FUN_00083880 @ 0x83880; LFCLK stop tail veneer. */
extern void g1_nrfx_clock_stop_checked(int domain);
void g1_nrfx_clock_stop_lfclk(void) { g1_nrfx_clock_stop_checked(0); }
