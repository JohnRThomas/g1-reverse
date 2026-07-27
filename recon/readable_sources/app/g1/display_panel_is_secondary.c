#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_g1_device_runtime_state__param_0027    [param_0027; G1-original]
 * Raw function identity: 0x0002bed0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0002bed0 @ 0x0002bed0
 * public-name: display_panel_is_secondary
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   signal_persist_task_event                <= FUN_0007cdf8 @ 0x0007cdf8
 * address symbols (name @ address):
 *   g_persist_task_status_lock               @ 0x20018d9c
 */
/* Reconstructed check_battery_critical @ 0x2bed0  (parity: 300/300 trials, PROVEN) */

extern void signal_persist_task_event(void);
int display_panel_is_secondary(unsigned long param_1) {
    volatile unsigned char *pcVar1 = (volatile unsigned char*)((unsigned long)&g_persist_task_status_lock) /*=0x20018d9c*/;
    while(*pcVar1 != 0){
        signal_persist_task_event();
    }
    return (unsigned int)(1 < *(unsigned char*)(param_1+0xd5));
}
