#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d578 @ 0x0004d578
 * public-name: g1_recon_z_log_msg_free
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_log_msg_pool_ptr                       @ 0x2000a0cc
 */
/* Reconstructed g1_recon_z_log_msg_free @ 0x4d578  owned extent: 0xe bytes.
 * Raw/address back-map: g1_recon_z_log_msg_free <= FUN_0004d578 @ 0x0004d578.
 */

#include <stdint.h>

struct mpsc_buffer;
/* mpsc_pbuf_free <= FUN_0004bfc8 @ 0x0004bfc8 */
extern void mpsc_pbuf_free(struct mpsc_buffer *buffer,
                           volatile uint32_t *item);

void g1_recon_z_log_msg_free(volatile uint32_t *item)
{
    struct mpsc_buffer *buffer =
        *(struct mpsc_buffer * volatile *)((unsigned long)&g_log_msg_pool_ptr) /*=0x2000a0cc*/;
    mpsc_pbuf_free(buffer, item);
}
