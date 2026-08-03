#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103a8cc @ 0x0103a8cc
 * public-name: thunk_FUN_0103b0e8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_busy_wait                       <= FUN_0103b0e8 @ 0x0103b0e8
 */
/* net-core thunk_FUN_0103b0e8 @ 0x0103a8cc: exact tail alias of FUN_0103b0e8. */
#include <stdint.h>
extern void z_impl_k_busy_wait(int32_t);
void thunk_FUN_0103b0e8(int32_t a){z_impl_k_busy_wait(a);}
