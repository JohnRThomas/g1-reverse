#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101dd9c @ 0x0101dd9c
 * public-name: FUN_0101dd9c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_timeout_list                           @ 0x2100113c
 */
/* net-core FUN_0101dd9c @ 0x0101dd9c */
#include <stdint.h>
uint32_t FUN_0101dd9c(void){return *(volatile uint32_t *)((unsigned long)&g_timeout_list) /*=0x2100113c*/;}
