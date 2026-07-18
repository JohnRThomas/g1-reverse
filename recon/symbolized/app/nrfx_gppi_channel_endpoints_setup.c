#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000850dc @ 0x000850dc
 * public-name: nrfx_gppi_channel_endpoints_setup
 * durable-map: recon/catalogs/function_names_app.json
 */
/* Reconstructed g1_recon_nrfx_gppi_channel_endpoints_setup @ 0x850dc.
 * Raw identity/back-map: FUN_000850dc.  Parity: 300/300 trials, PROVEN.
 * This is the asserted firmware wrapper, not net_buf_simple_push_mem.
 */

extern void nrfx_gppi_event_endpoint_setup(unsigned int, unsigned int);
extern void nrfx_gppi_task_endpoint_setup(unsigned int, unsigned int);

void nrfx_gppi_channel_endpoints_setup(
    unsigned int channel, unsigned int event_endpoint,
    unsigned int task_endpoint)
{
    nrfx_gppi_event_endpoint_setup(channel, event_endpoint);
    nrfx_gppi_task_endpoint_setup(channel, task_endpoint);
}
