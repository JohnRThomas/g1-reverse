#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003441c @ 0x0003441c
 * public-name: msg_content_decrement_timer
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   msg_content_decrement_timer              <= FUN_0003441c @ 0x0003441c
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 *   g_message_pool_index                     @ 0x2001a22a
 */
/* Reconstructed FUN_0003441c @ 0x3441c  (parity: 300/300 trials, PROVEN) */

void msg_content_decrement_timer(void)
{
    unsigned int idx = *(volatile unsigned char*)((unsigned long)&g_message_pool_index) /*=0x2001a22a*/;
    unsigned int base = idx * 0x1b4 + ((unsigned long)g_message_pool) /*=0x20007dac*/;
    int iVar1 = *(volatile int*)(base + 4);
    if (iVar1 != 0) {
        *(volatile int*)(base + 4) = iVar1 - 10;
    }
}
