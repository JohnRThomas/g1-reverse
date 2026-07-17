#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103a294 @ 0x0103a294
 * public-name: FUN_0103a294
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_0103a294 @ 0x0103a294 (true code extent 0x12) */
#include <stdint.h>
uint32_t FUN_0103a294(uint32_t *p){
  return __atomic_fetch_add(p,1,__ATOMIC_ACQ_REL);
}
