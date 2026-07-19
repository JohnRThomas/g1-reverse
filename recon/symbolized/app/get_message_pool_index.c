#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00034390 @ 0x00034390
 * public-name: get_message_pool_index
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_message_pool_index                   <= FUN_00034390 @ 0x00034390
 * address symbols (name @ address):
 *   g_message_pool_index                     @ 0x2001a22a
 */
/* Reconstructed FUN_00034390 @ 0x34390  (parity: 300/300 trials, PROVEN) */

unsigned char get_message_pool_index(void) {
    return *(volatile unsigned char*)((unsigned long)&g_message_pool_index) /*=0x2001a22a*/;
}
