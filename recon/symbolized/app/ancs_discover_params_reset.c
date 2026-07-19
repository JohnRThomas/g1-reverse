#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000191d8 @ 0x000191d8
 * public-name: ancs_discover_params_reset
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ancs_discover_params_reset               <= FUN_000191d8 @ 0x000191d8
 *   ancs_discover_ctx_clear                  <= FUN_0007f8c6 @ 0x0007f8c6
 * address symbols (name @ address):
 *   g_ancs_discover_params                   @ 0x20006abc
 */
/* Reconstructed FUN_000191d8 @ 0x191d8  (parity: 300/300 trials, PROVEN) */

extern void ancs_discover_ctx_clear(unsigned int);
void ancs_discover_params_reset(void)
{
    ancs_discover_ctx_clear(((unsigned long)&g_ancs_discover_params) /*=0x20006abc*/);
}
