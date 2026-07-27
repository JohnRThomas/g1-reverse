#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_g1_device_runtime_state__param_0027    [param_0027; G1-original]
 * Raw function identity: 0x0002be64.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_0002be64 @ 0x0002be64
 * public-name: now_has_persist_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   signal_persist_task_event                <= FUN_0007cdf8 @ 0x0007cdf8
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_persist_task_status_lock               @ 0x20018d9c
 */
/* Reconstructed now_has_persist_task @ 0x2be64  (parity: 300/300 trials, PROVEN) */

extern void signal_persist_task_event(void);
extern void log_message(unsigned long, ...);
extern void debug_print(unsigned long, ...);

unsigned char now_has_persist_task(unsigned char *param_1, unsigned int param_2)
{
    volatile unsigned char *pcVar1 = (volatile unsigned char*)((unsigned long)&g_persist_task_status_lock) /*=0x20018d9c*/;
    while (*pcVar1 != 0) {
        signal_persist_task_event();
    }
    int *p = *(int**)(param_1 + 0x1054);
    unsigned int uVar3 = *((unsigned char*)p + 4);
    unsigned char uVar2 = 0;
    if (uVar3 > 1) {
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 3) {
            if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message();
            } else {
                debug_print();
            }
        }
        uVar2 = 1;
    }
    return uVar2;
}
