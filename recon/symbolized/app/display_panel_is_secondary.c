#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002bed0 @ 0x0002bed0
 * public-name: display_panel_is_secondary
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_persist_task_status_lock               @ 0x20018d9c
 */
/* Reconstructed check_battery_critical @ 0x2bed0  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007cdf8(void);
unsigned int check_battery_critical(int param_1){
    volatile unsigned char *pcVar1 = (volatile unsigned char*)((unsigned long)&g_persist_task_status_lock) /*=0x20018d9c*/;
    while(*pcVar1 != 0){
        FUN_0007cdf8();
    }
    return (unsigned int)(1 < *(unsigned char*)(param_1+0xd5));
}
