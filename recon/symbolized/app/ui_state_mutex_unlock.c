#include "g1_app_symbols.h"
struct k_mutex;
/* readable reconstruction; identity: FUN_00026850 @ 0x00026850
 * public-name: ui_state_mutex_unlock
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ui_state_mutex_unlock                    <= FUN_00026850 @ 0x00026850
 *   k_mutex_unlock                           <= FUN_00072558 @ 0x00072558
 * address symbols (name @ address):
 *   g_ui_state_mutex                         @ 0x20007b3c
 */
/* Reconstructed FUN_00026850 @ 0x26850  (parity: 300/300 trials, PROVEN) */

extern int k_mutex_unlock(struct k_mutex *);
void ui_state_mutex_unlock(void) {
    k_mutex_unlock(((unsigned long)&g_ui_state_mutex) /*=0x20007b3c*/);
}
