#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033cdc @ 0x00033cdc
 * public-name: msg_content_used_count
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   msg_content_used_count                   <= FUN_00033cdc @ 0x00033cdc
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 */
/* Reconstructed FUN_00033cdc @ 0x33cdc  (parity: 300/300 trials, PROVEN) */

unsigned int msg_content_used_count(void)
{
    unsigned int uVar1 = 0;
    unsigned int base = ((unsigned long)g_message_pool) /*=0x20007dac*/;
    while (1) {
        if (*(volatile unsigned char*)(base + 0x10) == 0) {
            return uVar1 & 0xff;
        }
        uVar1 = uVar1 + 1;
        base = base + 0x1b4;
        if (uVar1 == 10) {
            break;
        }
    }
    return 10;
}
