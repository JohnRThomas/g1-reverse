#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039fb2 @ 0x01039fb2
 * public-name: FUN_01039fb2
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_mutex_unlock                    <= FUN_0103657c @ 0x0103657c
 */
/* net-core FUN_01039fb2 @ 0x01039fb2: exact tail alias of FUN_0103657c. */
#include <stdint.h>
extern uint32_t z_impl_k_mutex_unlock(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t FUN_01039fb2(uint32_t a,uint32_t b,uint32_t c,uint32_t d){return z_impl_k_mutex_unlock(a,b,c,d);}
