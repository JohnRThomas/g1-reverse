#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d578 @ 0x0004d578
 * public-name: mpsc_pbuf_free
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mpsc_pbuf_free                           <= FUN_0004d578 @ 0x0004d578
 * address symbols (name @ address):
 *   g_log_msg_pool_ptr                       @ 0x2000a0cc
 */
/* Reconstructed FUN_0004d578 @ 0x4d578  owned extent: 0xe bytes */

#include <stdint.h>

struct mpsc_buffer;
extern void FUN_0004bfc8(struct mpsc_buffer *buffer,
                         volatile uint32_t *item);

void mpsc_pbuf_free(volatile uint32_t *item)
{
    struct mpsc_buffer *buffer =
        *(struct mpsc_buffer * volatile *)((unsigned long)&g_log_msg_pool_ptr) /*=0x2000a0cc*/;
    FUN_0004bfc8(buffer, item);
}
