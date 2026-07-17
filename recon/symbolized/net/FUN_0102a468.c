#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102a468 @ 0x0102a468
 * public-name: FUN_0102a468
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_ctrl_report_len                    @ 0x210045e4
 */
/* net-core FUN_0102a468 @ 0x0102a468 */
#include <stdint.h>
uint32_t FUN_0102a468(void){return *(volatile uint32_t*)((unsigned long)&g_net_ctrl_report_len) /*=0x210045e4*/;}
