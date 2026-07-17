#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01039fb6 @ 0x01039fb6
 * public-name: atomic_set
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   atomic_set                               <= FUN_01039fb6 @ 0x01039fb6
 */
/* net-core FUN_01039fb6 @ 0x01039fb6 (true code extent 0x0e) */
#include <stdint.h>
uint32_t *atomic_set(uint32_t *p,uint32_t value){
  (void)__atomic_exchange_n(p,value,__ATOMIC_ACQ_REL);
  return p;
}
