#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000181f0 @ 0x000181f0
 * public-name: FUN_000181f0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_ancs_notify_sync_obj                   @ 0x20002310
 */
/* Reconstructed FUN_000181f0 @ 0x181f0  (parity: 300/300 trials, PROVEN) */

extern int FUN_0004f500(void *a);
int FUN_000181f0(void) {
    return FUN_0004f500((void*)((unsigned long)&g_ancs_notify_sync_obj) /*=0x20002310*/);
}
