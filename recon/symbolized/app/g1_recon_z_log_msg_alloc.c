#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d55c @ 0x0004d55c
 * public-name: g1_recon_z_log_msg_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   g1_recon_z_log_msg_alloc                 <= FUN_0004d55c @ 0x0004d55c
 * address symbols (name @ address):
 *   g_log_msg_mpsc_buffer                    @ 0x20003648
 */
/* Reconstructed FUN_0004d55c @ 0x4d55c. */
/* mpsc_pbuf_alloc <= FUN_0004bc8c @ 0x0004bc8c.  k_timeout_t is two words. */
extern int mpsc_pbuf_alloc(void *object, unsigned int value,
                           unsigned int low, unsigned int high);

int g1_recon_z_log_msg_alloc(unsigned int param_1)
{
    return mpsc_pbuf_alloc((void *)((unsigned long)&g_log_msg_mpsc_buffer) /*=0x20003648*/, param_1, 0, 0);
}
