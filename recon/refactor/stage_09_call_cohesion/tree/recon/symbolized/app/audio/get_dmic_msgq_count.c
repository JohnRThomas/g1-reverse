#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002ecf4 @ 0x0002ecf4
 * public-name: get_dmic_msgq_count
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_dmic_msgq_count                      <= FUN_0002ecf4 @ 0x0002ecf4
 * address symbols (name @ address):
 *   g_dmic_msgq                              @ 0x20007b7c
 */
/* Reconstructed FUN_0002ecf4 @ 0x2ecf4  (parity: 300/300 trials, PROVEN) */

unsigned int get_dmic_msgq_count(void) {
    return *(volatile unsigned int *)(((unsigned long)&g_dmic_msgq) /*=0x20007b7c*/ + 0x24);
}
