#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00018300 @ 0x00018300
 * public-name: FUN_00018300
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_9a436                             @ 0x0009a436
 *   g_ancs_active_conn                       @ 0x20006ab8
 */
/* Reconstructed FUN_00018300 @ 0x18300  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(int);
extern void FUN_00072880(int);
extern void change_work_mode_to(int);
void FUN_00018300(int param_1, unsigned int param_2)
{
    DEBUG_PRINT(((unsigned long)&rodata_9a436) /*=0x9a436*/);
    if (99 < param_2) {
        FUN_00072880(*(volatile int*)((unsigned long)&g_ancs_active_conn) /*=0x20006ab8*/ + 0x230);
        if (param_2 == 0x1f2) {
            change_work_mode_to(1);
            return;
        }
    }
}
