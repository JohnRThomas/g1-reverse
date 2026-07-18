#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102e1fc @ 0x0102e1fc
 * public-name: z_log_msg_commit
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_log_msg_commit                         <= FUN_0102e1fc @ 0x0102e1fc
 * address symbols (name @ address):
 *   g_net_periodic_work_obj                  @ 0x2100086c
 */
/* Reconstructed z_log_msg_commit @ 0x0102e1fc.
 * Raw/address back-map: FUN_0102e1fc / 0x0102e1fc.
 */
#include <stdint.h>

extern void FUN_0102cd8c(void *buffer, void *message); /* msg_commit */
extern void FUN_0102e140(void);                       /* z_log_msg_post_finalize */

void z_log_msg_commit(uint8_t *message)
{
    uint32_t (*timestamp_get)(void) =
        *(uint32_t (**)(void))0x2100461cu;
    *(uint32_t *)(message + 8) = timestamp_get();
    FUN_0102cd8c((void *)((unsigned long)&g_net_periodic_work_obj) /*=0x2100086c*/, message);
    FUN_0102e140();
}
