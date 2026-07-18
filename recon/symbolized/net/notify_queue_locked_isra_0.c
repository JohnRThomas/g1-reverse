#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103b25a @ 0x0103b25a
 * public-name: notify_queue_locked_isra_0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   notify_queue_locked_isra_0               <= FUN_0103b25a @ 0x0103b25a
 */
/* net-core FUN_0103b25a @ 0x103b25a  (parity 300 trials PROVEN) */

extern void FUN_01037e10(int,int);
void notify_queue_locked_isra_0(int param_1)
{
    if (param_1 != 0) {
        FUN_01037e10(param_1 + 0xa0, 0);
    }
}
