/* readable reconstruction; identity: FUN_0102de38 @ 0x0102de38
 * public-name: FUN_0102de38
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_tick_correction_pending            @ 0x21004664
 */
/* net-core FUN_0102de38 @ 0x0102de38 (true code extent 0x14) */
#include <stdint.h>
uint32_t FUN_0102de38(void){
  return __atomic_exchange_n((uint32_t *)0x21004664u,0,__ATOMIC_ACQ_REL);
}
