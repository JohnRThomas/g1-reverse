#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0008387a @ 0x0008387a
 * public-name: g1_nrfx_clock_stop_hfclk192m
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_nrfx_clock_stop_checked               <= FUN_00065324 @ 0x00065324
 *   g1_nrfx_clock_stop_hfclk192m             <= FUN_0008387a @ 0x0008387a
 */
/* Reconstructed FUN_0008387a @ 0x8387a; HFCLK192M stop tail veneer. */
extern void g1_nrfx_clock_stop_checked(int domain);
void g1_nrfx_clock_stop_hfclk192m(void) { g1_nrfx_clock_stop_checked(2); }
