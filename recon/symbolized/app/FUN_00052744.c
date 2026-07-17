#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00052744 @ 0x00052744
 * public-name: FUN_00052744
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   net_buf_put                              <= FUN_0005f200 @ 0x0005f200
 *   k_work_submit_to_queue                   <= FUN_000865fc @ 0x000865fc
 * address symbols (name @ address):
 *   smp_work_queue                           @ 0x20005bb8
 */
/* Reconstructed FUN_00052744 @ 0x52744  (parity: 300/300 trials, PROVEN) */

extern void net_buf_put(unsigned int a);
extern void k_work_submit_to_queue(unsigned int a, unsigned int b);

void FUN_00052744(int param_1)
{
    net_buf_put(param_1 + 0x10);
    k_work_submit_to_queue(((unsigned long)&smp_work_queue) /*=0x20005bb8*/, param_1);
}
