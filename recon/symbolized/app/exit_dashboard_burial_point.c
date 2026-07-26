#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0004aab0 @ 0x0004aab0
 * public-name: exit_dashboard_burial_point
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_dashboard_sum_time                   <= FUN_0004a960 @ 0x0004a960
 *   get_current_burial_point_type            <= FUN_0007dac0 @ 0x0007dac0
 *   accumulate_burial_point_duration         <= FUN_0007db50 @ 0x0007db50
 * address symbols (name @ address):
 *   rodata_f03c4                             @ 0x000f03c4   [INLINED -- G6 literal batch]
 *   rodata_f0459                             @ 0x000f0459   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed exit_dashboard_burial_point @ 0x4aab0  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_device_info(void);
extern unsigned int get_current_burial_point_type(void);
extern long long get_dashboard_sum_time(void);
extern unsigned int accumulate_burial_point_duration(void);

/* G7-B2 defect fix.  The body was `unsigned int` and assigned the result of
 * the logging call to the variable it returned.  Both sinks are `void`
 * (recon/headers/g1_log.h).  The shipped function computes no return value:
 * every exit is `add sp, #0xc; pop {r4, r5, pc}` at 0x4ab0a with r0 left
 * holding whatever the last call returned, and the sole caller,
 * ui_DashBoard_task.c:649, discards it.  The `r0v` chain was the decompiler
 * tracking r0's incidental content.  The five-argument shape of the two
 * logging calls is CORRECT and unchanged -- 0x4aaf0..0x4ab04 loads r0, r1, r2,
 * r3 and one stacked word at [sp]. */
void exit_dashboard_burial_point(void)
{
    unsigned int base;
    unsigned int uVar2;
    unsigned long long uVar4;
    unsigned int uVar3;

    base = get_device_info() + 0x1000;
    if (*(volatile unsigned char*)(base + 0x92) != 0) {
        uVar2 = get_current_burial_point_type();
        if (uVar2 < 7) {
            base = get_device_info() + 0x1000;
            *(volatile unsigned char*)(base + 0x92) = 0;
            uVar4 = (unsigned long long)get_dashboard_sum_time();
            uVar3 = (unsigned int)(uVar4 >> 32);
            (void)accumulate_burial_point_duration();
            if (1 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
                if (*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    base = get_device_info() + 0x1000;
                    log_message(((unsigned long)"%s(): [exit_dashboard_burial_point] sum_time is %d ms,dashboard_sum_time is %d s\n") /*=0xf03c4*/, ((unsigned long)"exit_dashboard_burial_point") /*=0xf0459*/, (unsigned int)uVar4, uVar3, *(volatile unsigned int*)(base + 0xd2));
                } else {
                    base = get_device_info() + 0x1000;
                    debug_print(((unsigned long)"%s(): [exit_dashboard_burial_point] sum_time is %d ms,dashboard_sum_time is %d s\n") /*=0xf03c4*/, ((unsigned long)"exit_dashboard_burial_point") /*=0xf0459*/, (unsigned int)uVar4, uVar3, *(volatile unsigned int*)(base + 0xd2));
                }
            }
        }
    }
}
