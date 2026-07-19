#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d8b8 @ 0x0004d8b8
 * public-name: g1_recon_z_log_msg_commit
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_log_msg_post_finalize                  <= FUN_0004d7d8 @ 0x0004d7d8
 *   g1_recon_z_log_msg_commit                <= FUN_0004d8b8 @ 0x0004d8b8
 * address symbols (name @ address):
 *   g_200027f8                               @ 0x200027f8
 *   g_log_msg_mpsc_buffer                    @ 0x20003648
 */
/* Reconstructed FUN_0004d8b8 @ 0x4d8b8
 * CFG_VERIFY_CALL_ARITIES=0,2,0
 * Readable identity: z_log_msg_commit.
 * Raw/address backmap: z_log_msg_commit <= FUN_0004d8b8 @ 0x0004d8b8.
 */

#include <stdint.h>

typedef uint32_t (*timestamp_fn_t)(void);

/* mpsc_pbuf_commit <= FUN_0004be0c @ 0x0004be0c */
extern void mpsc_pbuf_commit(void *buffer, void *message);
extern void z_log_msg_post_finalize(void); /* z_log_msg_post_finalize */

void g1_recon_z_log_msg_commit(void *message)
{
    timestamp_fn_t timestamp =
        *(timestamp_fn_t volatile *)((unsigned long)&g_200027f8) /*=0x200027f8*/;

    *(volatile uint32_t *)((uintptr_t)message + 8U) = timestamp();
    mpsc_pbuf_commit((void *)((unsigned long)&g_log_msg_mpsc_buffer) /*=0x20003648*/, message);
    z_log_msg_post_finalize();
}
