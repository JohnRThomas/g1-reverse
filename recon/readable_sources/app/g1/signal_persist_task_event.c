#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007cdf8 @ 0x0007cdf8
 * public-name: signal_persist_task_event
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 *   signal_persist_task_event                <= FUN_0007cdf8 @ 0x0007cdf8
 */
/* Reconstructed FUN_0007cdf8 @ 0x7cdf8  (parity: 300/300 trials, PROVEN) */

extern void k_sleep(unsigned int, unsigned int);
void signal_persist_task_event(void)
{
    k_sleep(0x21, 0);
}
