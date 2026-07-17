#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004d55c @ 0x0004d55c
 * public-name: FUN_0004d55c
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_log_msg_mpsc_buffer                    @ 0x20003648
 */
/* Reconstructed FUN_0004d55c @ 0x4d55c. */
extern int FUN_0004bc8c(void *object, unsigned int value,
                      unsigned int low, unsigned int high);

int FUN_0004d55c(unsigned int param_1)
{
    return FUN_0004bc8c((void *)((unsigned long)&g_log_msg_mpsc_buffer) /*=0x20003648*/, param_1, 0, 0);
}
