#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d588 @ 0x0004d588
 * public-name: z_log_msg_pending
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_log_msg_mpsc_buffer                    @ 0x20003648
 */
/* Reconstructed z_log_msg_pending @ 0x0004d588 (6 executable bytes).
 * Raw identity/back-map: FUN_0004d588.
 * The literal at 0x0004d590 and alignment NOP at 0x0004d58e are not code.
 */
#include <stdbool.h>

struct mpsc_pbuf_buffer;

extern bool mpsc_pbuf_is_pending(struct mpsc_pbuf_buffer *buffer); /* FUN_0007e50c */
#define g_log_msg_mpsc_buffer \
    (*(struct mpsc_pbuf_buffer *)((unsigned long)&g_log_msg_mpsc_buffer) /*=0x20003648*/) /* address back-map */

bool z_log_msg_pending(void)
{
    return mpsc_pbuf_is_pending(&g_log_msg_mpsc_buffer);
}
