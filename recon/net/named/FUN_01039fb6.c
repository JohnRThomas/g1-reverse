/* readable reconstruction; identity: FUN_01039fb6 @ 0x01039fb6
 * public-name: FUN_01039fb6
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01039fb6 @ 0x01039fb6 (true code extent 0x0e) */
#include <stdint.h>
uint32_t *FUN_01039fb6(uint32_t *p,uint32_t value){
  (void)__atomic_exchange_n(p,value,__ATOMIC_ACQ_REL);
  return p;
}
