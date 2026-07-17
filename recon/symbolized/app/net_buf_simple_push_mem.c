#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000850dc @ 0x000850dc
 * public-name: net_buf_simple_push_mem
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   nrfx_gppi_task_endpoint_setup            <= FUN_00064f78 @ 0x00064f78
 *   net_buf_simple_push_mem                  <= FUN_000850dc @ 0x000850dc
 */
/* Reconstructed FUN_000850dc @ 0x850dc  (parity: 300/300 trials, PROVEN) */

extern void FUN_00064f48(void);
extern void nrfx_gppi_task_endpoint_setup(unsigned int, unsigned int);

void net_buf_simple_push_mem(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    FUN_00064f48();
    nrfx_gppi_task_endpoint_setup(param_1, param_3);
}
