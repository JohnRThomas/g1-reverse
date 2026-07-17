/* readable reconstruction; identity: FUN_01025c38 @ 0x01025c38
 * public-name: FUN_01025c38
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_task_state_struct                  @ 0x21001c88
 */
/* net-core FUN_01025c38 @ 0x1025c38  (parity 300 trials PROVEN) */

#include <stdint.h>
static volatile uint8_t * const DAT_01025c40 = (volatile uint8_t *)0x21001c88;
void FUN_01025c38(void) { *(DAT_01025c40 + 0x1e) = 1; }
