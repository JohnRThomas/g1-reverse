#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01009204 @ 0x01009204
 * public-name: FUN_01009204
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_21000a68                               @ 0x21000a68
 */
/* net-core FUN_01009204 @ 0x01009204 */
#include <stdint.h>
typedef uint32_t (*callback4_t)(uint32_t,uint32_t,uint32_t,uint32_t);
uint32_t FUN_01009204(uint32_t a,uint32_t b,uint32_t c,uint32_t d){
  callback4_t fn=*(callback4_t volatile*)((unsigned long)&g_21000a68) /*=0x21000a68*/; return fn(a,b,c,d);
}
