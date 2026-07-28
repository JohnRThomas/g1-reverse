#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00034944 @ 0x00034944
 * public-name: notification_system_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   msg_content_decrement_timer              <= FUN_0003441c @ 0x0003441c
 *   notification_system_init                 <= FUN_00034944 @ 0x00034944
 *   dump_whitelist_init                      <= FUN_00035744 @ 0x00035744
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 *   g_message_pending_state                  @ 0x2001a229
 *   g_message_pool_index                     @ 0x2001a22a
 *   g_message_table_slot_count               @ 0x2001a22b
 */
/* Reconstructed FUN_00034944 @ 0x34944  (parity: 300/300 trials, PROVEN) */

extern void msg_content_decrement_timer(void);
extern void memset_bytes(void*, int, int);
extern void dump_whitelist_init(void);

void notification_system_init(void)
{
    *(volatile unsigned char *)((unsigned long)&g_message_table_slot_count) /*=0x2001a22b*/ = 10;
    *(volatile unsigned char *)((unsigned long)&g_message_pool_index) /*=0x2001a22a*/ = 0;
    *(volatile unsigned char *)((unsigned long)&g_message_pending_state) /*=0x2001a229*/ = 0;
    /* shipped 0x34946 `movs r0,#0' sets the memset fill BEFORE the call;
     * FUN_0003441c/msg_content_decrement_timer is void and never writes r0. */
    msg_content_decrement_timer();
    memset_bytes(((unsigned long)g_message_pool) /*=0x20007dac*/, 0, 0x2210);
    dump_whitelist_init();
}
