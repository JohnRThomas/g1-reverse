#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010318d8 @ 0x010318d8
 * public-name: FUN_010318d8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   k_work_submit_to_queue                   <= FUN_0103b268 @ 0x0103b268
 */
/* net-core FUN_010318d8 @ 0x10318d8  (parity 300 trials PROVEN) */

#include <stdint.h>
extern void k_work_submit_to_queue(uint32_t, uint32_t);
void FUN_010318d8(void) {
    k_work_submit_to_queue(G1N_210042f0, G1N_21004974);
}
