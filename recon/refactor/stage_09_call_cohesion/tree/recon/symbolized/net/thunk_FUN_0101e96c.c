#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102679e @ 0x0102679e
 * public-name: thunk_FUN_0101e96c
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core thunk_FUN_0101e96c @ 0x0102679e: exact tail alias of FUN_0101e96c. */
#include <stdint.h>
extern uint32_t FUN_0101e96c(uint16_t*);
uint32_t thunk_FUN_0101e96c(uint16_t *a){return FUN_0101e96c(a);}
