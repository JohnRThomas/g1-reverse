/* readable reconstruction; identity: FUN_000658dc @ 0x000658dc
 * public-name: set_ancs_notify_sync_fields
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   set_ancs_notify_sync_fields              <= FUN_000658dc @ 0x000658dc
 * address symbols (name @ address):
 *   g_ancs_notify_sync_field0_2bc8           @ 0x20002bc8
 *   g_ancs_notify_sync_field1_2bcc           @ 0x20002bcc
 */
/* Reconstructed FUN_000658dc @ 0x658dc  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
void set_ancs_notify_sync_fields(unsigned int param_1, unsigned int param_2)
{
    *(volatile uint32_t*)0x20002bc8UL = param_1;
    *(volatile uint32_t*)0x20002bccUL = param_2;
}
