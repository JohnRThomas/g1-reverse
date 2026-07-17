#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101b74c @ 0x0101b74c
 * public-name: FUN_0101b74c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_session_state_block                @ 0x210010a0
 */
/* net-core FUN_0101b74c @ 0x0101b74c */
#include <stdint.h>
uint32_t FUN_0101b74c(void){return *(volatile uint8_t*)((unsigned long)&g_net_session_state_block) /*=0x210010a0*/;}
