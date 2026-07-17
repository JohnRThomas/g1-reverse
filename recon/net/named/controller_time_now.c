/* readable reconstruction; identity: FUN_01022f08 @ 0x01022f08
 * public-name: controller_time_now
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core thunk_FUN_01025034 @ 0x01022f08: exact tail alias of FUN_01025034. */
#include <stdint.h>
extern uint64_t FUN_01025034(void);
uint64_t controller_time_now(void){return FUN_01025034();}
