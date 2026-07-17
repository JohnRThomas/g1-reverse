#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026850 @ 0x00026850
 * public-name: FUN_00026850
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 * address symbols (name @ address):
 *   g_ui_state_mutex                         @ 0x20007b3c
 */
/* Reconstructed FUN_00026850 @ 0x26850  (parity: 300/300 trials, PROVEN) */

extern void k_mutex_unlock(unsigned int);
void FUN_00026850(void) {
    k_mutex_unlock(((unsigned long)&g_ui_state_mutex) /*=0x20007b3c*/);
}
