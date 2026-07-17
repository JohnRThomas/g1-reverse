#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103b300 @ 0x0103b300
 * public-name: thunk_FUN_01038284
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core thunk_FUN_01038284 @ 0x0103b300: exact tail alias of FUN_01038284. */
#include <stdint.h>
extern uint64_t FUN_01038284(void);
uint64_t thunk_FUN_01038284(void){return FUN_01038284();}
