#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00036030 @ 0x00036030
 * public-name: set_new_message_pending_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_new_message_pending_flag             <= FUN_00036030 @ 0x00036030
 * address symbols (name @ address):
 *   g_new_message_pending_flag               @ 0x2001b80e
 */
/* Reconstructed FUN_00036030 @ 0x36030  (parity: 300/300 trials, PROVEN) */

void set_new_message_pending_flag(void)
{
    *(volatile unsigned char*)((unsigned long)&g_new_message_pending_flag) /*=0x2001b80e*/ = 1;
}
