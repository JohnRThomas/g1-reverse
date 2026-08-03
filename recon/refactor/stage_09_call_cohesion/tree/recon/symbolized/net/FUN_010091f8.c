#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010091f8 @ 0x010091f8
 * public-name: FUN_010091f8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_21000a64                               @ 0x21000a64
 */
/* net-core FUN_010091f8 @ 0x010091f8 */
#include <stdint.h>
typedef uint32_t (*callback4_t)(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t FUN_010091f8(uint32_t a,uint32_t b,uint32_t c,uint32_t d){
  callback4_t fn=*(callback4_t volatile*)((unsigned long)&g_21000a64) /*=0x21000a64*/; return fn(a,b,c,d);
}
